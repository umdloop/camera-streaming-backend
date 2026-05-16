#!/usr/bin/env bash
# Usage: sudo ./diagnose.sh <label> [duration_seconds] [gui_ip]
#   label: tag for this run, e.g. "online" or "offline"
#   duration_seconds: how long to capture (default 30)
#   gui_ip: optional, filters media-path summary to this peer
#
# Run once with internet up ("online"), once with it down ("offline"),
# then diff the two output directories.

set -u

LABEL="${1:-run}"
DURATION="${2:-30}"
GUI_IP="${3:-}"

if [[ $EUID -ne 0 ]]; then
    echo "Must run as root (tcpdump + strace need it). Try: sudo $0 $*" >&2
    exit 1
fi

OUT="diag_${LABEL}_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$OUT"
echo "Writing to $OUT/"

# ── Host state snapshot ──────────────────────────────────────────────────────
{
    echo "=== date ==="; date
    echo; echo "=== ip -4 addr ==="; ip -4 -o addr show scope global
    echo; echo "=== ip route ==="; ip route
    echo; echo "=== resolv.conf ==="; cat /etc/resolv.conf 2>/dev/null
    echo; echo "=== default iface ==="; ip route get 1.1.1.1 2>/dev/null || echo "(no default route)"
} > "$OUT/host_state.txt"

# ── Find backend PID ─────────────────────────────────────────────────────────
CAM_PID=$(pgrep -f camera-stream | head -1 || true)
if [[ -z "$CAM_PID" ]]; then
    echo "WARNING: camera-stream not running. Start it in another terminal, then re-run." >&2
else
    echo "Backend PID: $CAM_PID" | tee "$OUT/backend_pid.txt"
    ss -tunap 2>/dev/null | grep -E "camera-stream|pid=$CAM_PID" > "$OUT/backend_sockets.txt" || true
fi

# ── Start packet capture on all interfaces ───────────────────────────────────
# Excludes SSH so the capture doesn't include your own session traffic.
echo "Capturing packets for ${DURATION}s on all interfaces..."
tcpdump -i any -w "$OUT/capture.pcap" -s 0 'not port 22' \
    > "$OUT/tcpdump.log" 2>&1 &
TCPDUMP_PID=$!

# ── strace the backend's network syscalls ───────────────────────────────────
if [[ -n "$CAM_PID" ]]; then
    timeout "$DURATION" strace -f -e trace=network -tt -p "$CAM_PID" \
        > "$OUT/strace.log" 2>&1 &
    STRACE_PID=$!
fi

echo
echo "  >>> NOW: in another window, open the GUI and try to view a camera. <<<"
echo "  >>> Waiting ${DURATION}s... <<<"
echo

sleep "$DURATION"

# ── Stop captures ────────────────────────────────────────────────────────────
kill -INT "$TCPDUMP_PID" 2>/dev/null || true
wait "$TCPDUMP_PID" 2>/dev/null || true
[[ -n "${STRACE_PID:-}" ]] && wait "$STRACE_PID" 2>/dev/null || true

# ── Summaries (so you don't need Wireshark to see the obvious) ───────────────
SUMMARY="$OUT/SUMMARY.txt"
{
    echo "=== Capture summary ($LABEL) ==="
    echo

    echo "--- DNS queries (offline failures show here) ---"
    tcpdump -nn -r "$OUT/capture.pcap" 'port 53' 2>/dev/null \
        | grep -oE '\? [^ ]+' | sort -u | head -50
    echo

    echo "--- Unique non-LAN destinations contacted ---"
    tcpdump -nn -r "$OUT/capture.pcap" \
        'not arp and not port 22 and not net 192.168.0.0/16 and not net 10.0.0.0/8 and not net 172.16.0.0/12 and not net 169.254.0.0/16 and not net 224.0.0.0/4' \
        2>/dev/null | awk '{print $3" -> "$5}' | sed 's/[.:][0-9]*$//' | sort -u | head -50
    echo

    echo "--- All TCP/UDP endpoints (top 20 by packet count) ---"
    tcpdump -nn -r "$OUT/capture.pcap" 2>/dev/null \
        | awk '{print $3, "->", $5}' | sed 's/[.:][0-9]*$//g' \
        | sort | uniq -c | sort -rn | head -20
    echo

    if [[ -n "$GUI_IP" ]]; then
        echo "--- Media-path packet counts to/from $GUI_IP ---"
        echo "  Jetson -> GUI: $(tcpdump -nn -r "$OUT/capture.pcap" "dst host $GUI_IP and udp" 2>/dev/null | wc -l)"
        echo "  GUI -> Jetson: $(tcpdump -nn -r "$OUT/capture.pcap" "src host $GUI_IP and udp" 2>/dev/null | wc -l)"
        echo "  TCP signaling: $(tcpdump -nn -r "$OUT/capture.pcap" "host $GUI_IP and tcp port 8081" 2>/dev/null | wc -l)"
        echo
    fi

    echo "--- ICMP unreachables (shows what couldn't be reached) ---"
    tcpdump -nn -r "$OUT/capture.pcap" 'icmp' 2>/dev/null | head -20
    echo

    if [[ -f "$OUT/strace.log" ]]; then
        echo "--- Backend connect() / sendto() to non-local addresses ---"
        grep -E 'connect\(|sendto\(' "$OUT/strace.log" \
            | grep -vE 'AF_UNIX|127\.0\.0\.1|::1' \
            | head -30
    fi
} > "$SUMMARY"

echo
echo "Done. Key file: $SUMMARY"
echo "Full pcap:  $OUT/capture.pcap  (open in Wireshark for deep inspection)"
echo
echo "Once you have both diag_online_* and diag_offline_* directories, diff them:"
echo "  diff <(sort diag_online_*/SUMMARY.txt) <(sort diag_offline_*/SUMMARY.txt)"

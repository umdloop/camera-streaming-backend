#!/usr/bin/env bash
# Run me on the Jetson WITH WAN DISCONNECTED. Needs sudo.
#
# Usage: sudo ./diagnose_offline.sh <gui_ip> [test_seconds]
#
# Runs four scenarios offline and reports whether webrtcbin ICE reaches
# "connected". Each scenario needs you to open the GUI and view a camera
# within the test window when prompted.
#
# Scenarios:
#   A) baseline           — offline as-is
#   B) docker0 down       — remove docker0 from libnice's interface list
#   C) stub default route — add `default via <lan-gw>` metric 1000
#   D) B + C combined     — both at once
#
# All system state is restored at exit.

set -u

if [[ $EUID -ne 0 ]]; then
    echo "Must run as root. Try: sudo $0 $*" >&2
    exit 1
fi

GUI_IP="${1:-}"
SECS="${2:-25}"

if [[ -z "$GUI_IP" ]]; then
    echo "Usage: sudo $0 <gui_ip> [test_seconds]" >&2
    exit 1
fi

OUT="offline_diag_$(date +%Y%m%d_%H%M%S)"
mkdir -p "$OUT"
echo "Writing to $OUT/"

LAN_IFACE=$(ip -4 -o route get "$GUI_IP" 2>/dev/null | awk '{for(i=1;i<=NF;i++) if($i=="dev") print $(i+1)}' | head -1)
LAN_GW="192.168.88.1"   # adjust here if your LAN gateway differs
BINARY="./build/camera-stream"

if [[ ! -x "$BINARY" ]]; then
    echo "Backend binary not found at $BINARY — run from repo root." >&2
    exit 1
fi

echo "GUI IP:       $GUI_IP"
echo "LAN iface:    $LAN_IFACE"
echo "LAN gateway:  $LAN_GW (edit script if wrong)"
echo "Test window:  ${SECS}s per scenario"
echo

# ── Baseline system snapshot ─────────────────────────────────────────────────
{
    echo "=== date ==="; date
    echo; echo "=== ip -4 addr ==="; ip -4 -o addr
    echo; echo "=== ip route ==="; ip route
    echo; echo "=== ip route get $GUI_IP ==="; ip route get "$GUI_IP" 2>&1
    echo; echo "=== docker0 link ==="; ip link show docker0 2>&1 || echo "(no docker0)"
    echo; echo "=== nvpmodel -q ==="; nvpmodel -q 2>&1 || echo "(no nvpmodel)"
    echo; echo "=== jetson_clocks --show ==="; jetson_clocks --show 2>&1 | head -25 || true
} > "$OUT/system_state.txt"

# ── Helpers ──────────────────────────────────────────────────────────────────
run_scenario() {
    local name="$1"
    local logfile="$OUT/${name}.log"
    local pcapfile="$OUT/${name}.pcap"

    pkill -f camera-stream 2>/dev/null || true
    sleep 1

    echo "────────────────────────────────────────────────────────────────────"
    echo " Scenario: $name"
    echo "────────────────────────────────────────────────────────────────────"
    echo " State diff for this scenario:"
    ip route | grep -E 'default|docker0' || echo "  (no default or docker0 routes)"
    ip link show docker0 2>/dev/null | head -1 || true
    echo

    # Packet capture (only the GUI conversation, to keep files small)
    tcpdump -i any -w "$pcapfile" -s 0 "host $GUI_IP" \
        > /dev/null 2>&1 &
    local TCPDUMP_PID=$!

    # Start backend with ICE-focused debug
    GST_DEBUG='webrtcbin:5,webrtcice:5,nice:5' \
        "$BINARY" > "$logfile" 2>&1 &
    local CAM_PID=$!
    sleep 2

    echo "  >>> NOW: switch to the GUI machine, open a camera. <<<"
    echo "  >>> ${SECS}s window starting... <<<"
    sleep "$SECS"

    kill "$CAM_PID" 2>/dev/null || true
    kill -INT "$TCPDUMP_PID" 2>/dev/null || true
    wait "$CAM_PID" 2>/dev/null || true
    wait "$TCPDUMP_PID" 2>/dev/null || true

    # Score: did ICE reach "connected"?
    local ice_connected
    ice_connected=$(grep -c 'ICE connection state change from checking(1) to connected' "$logfile" || true)
    local ice_failed
    ice_failed=$(grep -c 'ICE connection state change from .* to failed' "$logfile" || true)
    local pkts_out
    pkts_out=$(tcpdump -nn -r "$pcapfile" "src host $(hostname -I | awk '{print $1}') and udp" 2>/dev/null | wc -l)
    local pkts_in
    pkts_in=$(tcpdump -nn -r "$pcapfile" "src host $GUI_IP and udp" 2>/dev/null | wc -l)

    {
        echo "scenario=$name"
        echo "ice_connected_transitions=$ice_connected"
        echo "ice_failed_transitions=$ice_failed"
        echo "udp_out_to_gui=$pkts_out"
        echo "udp_in_from_gui=$pkts_in"
    } > "$OUT/${name}.score"

    echo "  Result: ICE connected events=$ice_connected, failed=$ice_failed, UDP out/in=$pkts_out/$pkts_in"
    echo
}

# ── Cleanup trap ─────────────────────────────────────────────────────────────
cleanup() {
    pkill -f camera-stream 2>/dev/null || true
    # Restore docker0 if we touched it
    if [[ -n "${DOCKER_DOWNED:-}" ]]; then
        ip link set docker0 up 2>/dev/null || true
    fi
    # Remove any stub default route we added
    if [[ -n "${ROUTE_ADDED:-}" ]]; then
        ip route del default via "$LAN_GW" dev "$LAN_IFACE" metric 1000 2>/dev/null || true
    fi
    echo "Restored system state."
}
trap cleanup EXIT INT TERM

# ── A) baseline ──────────────────────────────────────────────────────────────
run_scenario "A_baseline"

# ── B) docker0 down ─────────────────────────────────────────────────────────
if ip link show docker0 &>/dev/null; then
    ip link set docker0 down
    DOCKER_DOWNED=1
fi
run_scenario "B_docker0_down"
if [[ -n "${DOCKER_DOWNED:-}" ]]; then
    ip link set docker0 up
    unset DOCKER_DOWNED
fi

# ── C) stub default route ───────────────────────────────────────────────────
if ip route add default via "$LAN_GW" dev "$LAN_IFACE" metric 1000 2>/dev/null; then
    ROUTE_ADDED=1
else
    echo "WARNING: could not add stub default route (gateway $LAN_GW may not be reachable on $LAN_IFACE)" >&2
fi
run_scenario "C_stub_default_route"
if [[ -n "${ROUTE_ADDED:-}" ]]; then
    ip route del default via "$LAN_GW" dev "$LAN_IFACE" metric 1000 2>/dev/null || true
    unset ROUTE_ADDED
fi

# ── D) docker0 down + stub default route ────────────────────────────────────
if ip link show docker0 &>/dev/null; then
    ip link set docker0 down
    DOCKER_DOWNED=1
fi
if ip route add default via "$LAN_GW" dev "$LAN_IFACE" metric 1000 2>/dev/null; then
    ROUTE_ADDED=1
fi
run_scenario "D_both"
if [[ -n "${ROUTE_ADDED:-}" ]]; then
    ip route del default via "$LAN_GW" dev "$LAN_IFACE" metric 1000 2>/dev/null || true
    unset ROUTE_ADDED
fi
if [[ -n "${DOCKER_DOWNED:-}" ]]; then
    ip link set docker0 up
    unset DOCKER_DOWNED
fi

# ── Build final report ──────────────────────────────────────────────────────
REPORT="$OUT/REPORT.txt"
{
    echo "############ OFFLINE DIAGNOSIS REPORT ############"
    echo "Generated: $(date)"
    echo "GUI IP: $GUI_IP    LAN iface: $LAN_IFACE    LAN gw: $LAN_GW"
    echo
    echo "============ SYSTEM STATE (baseline offline) ============"
    cat "$OUT/system_state.txt"
    echo
    echo "============ SCENARIO RESULTS ============"
    for f in "$OUT"/*.score; do
        echo "--- $(basename "$f" .score) ---"
        cat "$f"
        echo
    done
    echo "============ KEY: which scenarios reached ICE connected? ============"
    for f in "$OUT"/*.score; do
        name=$(basename "$f" .score)
        connected=$(grep '^ice_connected_transitions=' "$f" | cut -d= -f2)
        if [[ "${connected:-0}" -gt 0 ]]; then
            echo "  PASS  $name  (ICE connected $connected times)"
        else
            echo "  FAIL  $name"
        fi
    done
    echo
    echo "============ INTERESTING LOG LINES PER SCENARIO ============"
    for name in A_baseline B_docker0_down C_stub_default_route D_both; do
        echo "--- $name ---"
        log="$OUT/${name}.log"
        [[ -f "$log" ]] || { echo "(no log)"; continue; }
        # ICE state machine transitions
        grep -E 'ICE connection state change|ICE gathering state change|Peer connection state change' "$log" \
            | sed 's/\x1b\[[0-9;]*m//g' | head -30
        echo
        # Any libnice/webrtcice warnings or errors
        grep -E 'WARN|ERROR|fail|bind|no route' "$log" \
            | sed 's/\x1b\[[0-9;]*m//g' | head -20
        echo
    done
} > "$REPORT"

echo
echo "============================================================"
echo "Report written to: $REPORT"
echo "Pcaps and logs in: $OUT/"
echo "Share REPORT.txt back."
echo "============================================================"

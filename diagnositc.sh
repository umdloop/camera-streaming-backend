#!/usr/bin/env bash
# Quick diagnostic for the GUI "stuck on starting stream" issue.
# Run on the Jetson while mediamtx + the backend are running, and at least
# one camera is enabled (so it's publishing to MediaMTX).
#
#   ./diagnose_whep.sh              # uses defaults below
#   ./diagnose_whep.sh camera_4     # check a specific stream


set -u


STREAM="${1:-camera_4}"
HOST="${HOST:-192.168.88.90}"
WHEP_PORT="${WHEP_PORT:-8889}"
GUI_PORT="${GUI_PORT:-3000}"
ORIGIN="http://${HOST}:${GUI_PORT}"
URL="http://${HOST}:${WHEP_PORT}/${STREAM}/whep"


hr() { printf -- '─%.0s' {1..72}; echo; }
hdr() { hr; echo "▶ $*"; hr; }


hdr "Target: ${URL}    Origin: ${ORIGIN}"


hdr "1. Interfaces on this host"
ip -4 addr | awk '/inet /{print "  ", $NF, $2}'


hdr "2. Is mediamtx listening on the expected ports?"
ss -tlnp 2>/dev/null | grep -E ":(8554|8889|9997)\b" || echo "  (no matches — is mediamtx running?)"
echo "  UDP:"
ss -ulnp 2>/dev/null | grep -E ":8189\b" || echo "  (no UDP 8189 — webrtcLocalUDPAddress)"


hdr "3. WHEP CORS preflight (OPTIONS)"
curl -sS -i -X OPTIONS "${URL}" \
 -H "Origin: ${ORIGIN}" \
 -H "Access-Control-Request-Method: POST" \
 -H "Access-Control-Request-Headers: content-type" \
 --max-time 5 \
 | sed -n '1,25p'


hdr "4. WHEP POST with a minimal recvonly offer"
# Minimal SDP offer — enough for MediaMTX to answer if the stream exists.
OFFER=$(cat <<'EOF'
v=0
o=- 0 0 IN IP4 127.0.0.1
s=-
t=0 0
m=video 9 UDP/TLS/RTP/SAVPF 96
c=IN IP4 0.0.0.0
a=rtcp-mux
a=recvonly
a=ice-ufrag:abcd
a=ice-pwd:abcdefghijklmnopqrstuv
a=fingerprint:sha-256 00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00:00
a=setup:actpass
a=mid:0
a=rtpmap:96 H264/90000
EOF
)
curl -sS -i -X POST "${URL}" \
 -H "Origin: ${ORIGIN}" \
 -H "Content-Type: application/sdp" \
 --data-binary "${OFFER}" \
 --max-time 5 \
 | sed -n '1,40p'


hdr "5. MediaMTX paths (only works if api: yes)"
curl -sS --max-time 3 "http://127.0.0.1:9997/v3/paths/list" \
 || echo "  (API disabled — that's expected with mediamtx.yml; on locally use mediamtx.local.yml to enable)"


hr
echo "Done. Key things to look at:"
echo "  - Step 3 should return 200/204 with 'Access-Control-Allow-Origin' set"
echo "    to '*' or '${ORIGIN}'. If missing, the browser blocks the POST."
echo "  - Step 4 should return 201 Created with an SDP answer containing"
echo "    'a=candidate:' lines for ${HOST}. If 404, the stream isn't being"
echo "    published. If 4xx with no SDP, auth or path config is the issue."





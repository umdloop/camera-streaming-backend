# MediaMTX (WHEP) migration plan

Branch: `mediamtx-whep`

Goal: replace `webrtcbin` + custom ICE signaling with **MediaMTX as a sidecar**.
C++ backend keeps mission/camera control. Browser keeps the same UI.

**Deployment context (drives every config decision below):** rover with
**no internet, ever**. Known peers: Jetson at `192.168.88.90`, GUI at
`192.168.88.10`, both on the same `/24` LAN through a base-station gateway.
This means:

- No public STUN, no TURN, no DNS, no NTP. Anything that tries to reach the
  outside network is a bug, not a config option to leave at "default."
- Host candidates only. The LAN is flat — `srflx` and `relay` candidates are
  not just unnecessary, they're failure modes.
- IPs are stable. We can pin and hardcode where it makes the system more
  predictable.

## Architecture after

```
USB camera  ──►  gst pipeline  ──►  rtspclientsink ──►  MediaMTX (localhost:8554)
                                                              │
                                                              ▼
                                                       WHEP HTTP (8889)
                                                              │
                                                              ▼
                                                          Browser
```

WebSocket on 8081 stays — used for camera enable/disable, missions, config, stats.
**Media signaling (offer/answer/ICE) deleted entirely.**

## File-by-file changes

### `CMakeLists.txt`
- Drop `gstwebrtc-1.0` from `pkg_check_modules`. Drop `gstsdp-1.0` if only used by webrtc.
- No new deps — `rtspclientsink` lives in `gst-rtsp-server` plugins, which are runtime not build-time.

### `include/CameraPipeline.hpp`
- Remove: `OnIceCandidateCallback`, `OnOfferCreatedCallback`, `setRemoteAnswer`, `addIceCandidate`, `setOnIceCandidateCallback`, `setOnOfferCreatedCallback`, `webrtcbin_` field, `offerSourceId_`, `offerScheduled_`.
- Remove static handlers: `doCreateOffer`, `onNegotiationNeeded`, `onIceCandidate`, `onOfferCreated`.
- Add: constructor takes `streamName` (used to build RTSP URL); store as field.
- Includes: drop `<gst/webrtc/webrtc.h>`.

### `src/CameraPipeline.cpp`
- In `buildPipelineString`: replace tail
  ```
  ! webrtcbin name=webrtcbin bundle-policy=max-bundle
  ```
  with
  ```
  ! rtspclientsink location=rtsp://127.0.0.1:8554/<streamName>
                   protocols=tcp latency=0 name=sink
  ```
  (use `tcp` for loopback so we don't fight UDP buffer sizing inside the host)
- Delete all webrtcbin signal wiring in `start()`.
- Delete `doCreateOffer`, `onNegotiationNeeded`, `onIceCandidate`, `onOfferCreated`, `setRemoteAnswer`, `addIceCandidate`.
- Keep: stats probe, bus watch, error reporting, `start()`/`stop()`. The probe still lives on `h264parse` and gives fps/bitrate.

### `include/CameraManager.hpp`
- Remove: `OnOfferCallback`, `OnIceCallback`, `setOfferCallback`, `setIceCallback`, `setRemoteAnswer`, `addIceCandidate`.
- Remove fields: `onOffer_`, `onIce_`.

### `src/CameraManager.cpp`
- Remove method bodies for `setRemoteAnswer`, `addIceCandidate`.
- In pipeline creation: pass camera id as `streamName` to `CameraPipeline`.
- Remove the offer/ice callback wiring on each new pipeline (in the retry loop).

### `src/main.cpp`
- Delete the `setOfferCallback` / `setIceCallback` blocks (lines ~76-92).
- In `setOnMessageCallback`, delete the `"answer"` and `"ice"` branches.
- (Optional) Include the WHEP URL in `buildStateJson`. Or just let the frontend derive it from `location.hostname` — simpler. Doing the latter.

### `include/WsServer.hpp` / `src/WsServer.cpp`
- No changes. It's transport only.

### `web/index.html`
- Delete `STUN_URL` constant (already gone).
- **Change `WS_URL` to derive from `location.hostname`** so the page works
  when served from the Jetson (`http://192.168.88.90/`) or from a tunnel
  (`http://localhost/`) without code changes:
  ```js
  const WS_URL  = `ws://${location.hostname}:8081`;
  const WHEP_BASE = `http://${location.hostname}:8889`;
  ```
  For the rover topology (GUI on `192.168.88.10`, Jetson on `192.168.88.90`)
  this means: serve the HTML from the Jetson and have the GUI browser open
  `http://192.168.88.90/`. Both `WS_URL` and the WHEP fetch resolve correctly.
- Replace the `offer` / `answer` / `ice` message handlers (~25 lines) with a `startWhep(cameraId)` helper.
- Trigger `startWhep` when a camera transitions from disabled→enabled in the `state` message; trigger `stopWhep` on the reverse.

  ```js
  async function startWhep(id) {
    // iceServers: [] is critical — without it, the browser would default to
    // its built-in heuristics. Empty list = host candidates only, no STUN.
    const pc = new RTCPeerConnection({ iceServers: [] });
    pc.addTransceiver('video', { direction: 'recvonly' });
    pc.ontrack = (e) => {
      const v = document.getElementById(`video-${id}`);
      if (v) v.srcObject = e.streams[0];
    };
    const offer = await pc.createOffer();
    await pc.setLocalDescription(offer);
    const r = await fetch(`${WHEP_BASE}/${id}/whep`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/sdp' },
      body: offer.sdp,
    });
    if (!r.ok) throw new Error(`WHEP ${r.status}`);
    await pc.setRemoteDescription({ type: 'answer', sdp: await r.text() });
    pcs.set(id, pc);
  }

  function stopWhep(id) {
    pcs.get(id)?.close();
    pcs.delete(id);
  }
  ```

- Remove `STUN_URL` derivation, the `case 'offer':` and `case 'ice':` branches, and the corresponding outgoing `send({ type: 'answer' ... })` / `send({ type: 'ice' ... })` calls.

### New: `mediamtx.yml`

Pin **MediaMTX v1.9.x**. The YAML schema below targets that series — confirm
each key against the docs of the specific patch release you download
(`https://github.com/bluenviron/mediamtx/blob/v1.9.x/mediamtx.yml`).

The defaults include a public STUN server (`stun.l.google.com:19302`) — that
**must** be disabled for this deployment. Likewise, anything that gathers
candidates from interfaces other than `enP8p1s0` (e.g., `docker0` at
`172.17.0.1`) is a footgun we already saw with libnice. Pin the host
candidate explicitly.

```yaml
logLevel: info

# ── Servers we use ─────────────────────────────────────────────────────────
rtsp: yes
rtspAddress: :8554            # ingest from rtspclientsink on loopback
rtspTransports: [tcp]         # loopback — TCP is simpler than UDP buffer tuning

webrtc: yes
webrtcAddress: :8889          # WHEP HTTP endpoint
webrtcLocalUDPAddress: :8189  # WebRTC media UDP port (fixed; useful if firewall)
webrtcLocalTCPAddress: ''     # disable WebRTC-over-TCP fallback (LAN doesn't need it)

# ── Everything else off ────────────────────────────────────────────────────
hls: no
rtmp: no
srt: no
api: no                       # MediaMTX HTTP API; flip to yes if you want /v3/paths

# ── ICE config: airgapped LAN ──────────────────────────────────────────────
# No public STUN. No TURN. Host candidates only.
webrtcICEServers2: []

# Advertise EXACTLY the Jetson's LAN IP as the WebRTC host candidate. This
# stops MediaMTX from also offering 172.17.0.1 (docker0) or any wlan IP.
webrtcIPsFromInterfaces: no
webrtcAdditionalHosts:
  - 192.168.88.90

# ── Auth ───────────────────────────────────────────────────────────────────
# Publishers limited to loopback (= our backend). Readers = anyone on LAN.
# No passwords — this is a closed network with one device on it.
authMethod: internal
authInternalUsers:
  - user: any
    pass:
    ips: []
    permissions:
      - action: read
  - user: any
    pass:
    ips: [127.0.0.1/32]
    permissions:
      - action: publish

# ── Paths ──────────────────────────────────────────────────────────────────
# Accept any path name. The C++ backend chooses the path per camera id.
paths:
  all_others:
```

**Why each anti-internet key matters:**

| Key | What it prevents |
|---|---|
| `webrtcICEServers2: []` | MediaMTX won't try to contact `stun.l.google.com` (its default). No DNS lookup, no socket to anywhere off-LAN. |
| `webrtcIPsFromInterfaces: no` + `webrtcAdditionalHosts: [192.168.88.90]` | Stops advertisement of `172.17.0.1`, link-local addresses, or any wifi-NIC IP that may flap when WAN comes/goes. |
| `rtspTransports: [tcp]` | We're publishing over loopback. TCP avoids UDP buffer-size tuning entirely on the local hop. |
| `webrtcLocalTCPAddress: ''` | WebRTC-over-TCP exists for restrictive corporate networks. The rover LAN isn't one. Off. |
| `api: no` | Closes an HTTP surface we don't use. Flip on for debugging. |
| `hls/rtmp/srt: no` | Closes unused listeners. |

After you have it running, smoke-test with `curl`:

```bash
# From the Jetson: MediaMTX should be listening, with no outbound sockets.
sudo ss -tnlp | grep mediamtx
sudo ss -tunap | grep mediamtx       # should NOT show ESTABLISHED to anything off-LAN
```

### MediaMTX binary

Pin a specific version. As of this plan: **v1.9.x** (use the latest patch).
Confirm Jetson is `linux_arm64v8`.

The rover has no internet, so:

1. On a connected dev machine, download the release tarball:
   ```
   VER=1.9.3       # or the latest v1.9.x patch
   curl -LO https://github.com/bluenviron/mediamtx/releases/download/v${VER}/mediamtx_v${VER}_linux_arm64v8.tar.gz
   ```
2. Copy it to the rover via the base-station LAN (`scp`, USB drive, whatever
   the team usually uses for shipping artifacts to the rover).
3. On the Jetson, in the repo root:
   ```
   tar xf mediamtx_v${VER}_linux_arm64v8.tar.gz mediamtx
   chmod +x mediamtx
   ```

**Do not commit the binary.** Add to `.gitignore`:
```
mediamtx
mediamtx_*.tar.gz
```

Verify the binary doesn't depend on internet on startup:
```
strace -e trace=connect ./mediamtx mediamtx.yml 2>&1 | head -40
# Expected: connect() calls only to 127.0.0.1, 0.0.0.0, or :: (listen sockets).
# Anything to a public IP would be a misconfiguration in mediamtx.yml.
```

### New: `run.sh` (replaces direct binary invocation)
Launches MediaMTX as a sidecar with cleanup:

```bash
#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

./mediamtx mediamtx.yml &
MEDIAMTX_PID=$!
trap "kill $MEDIAMTX_PID 2>/dev/null || true" EXIT INT TERM

# Wait for MediaMTX to come up
for _ in {1..20}; do
    nc -z 127.0.0.1 8554 && break
    sleep 0.1
done

./build/camera-stream "$@"
```

## Build & run

```bash
git checkout -b mediamtx-whep
# (apply all the edits above)

# On the Jetson:
cmake --build build
./run.sh
```

Then open the web GUI in the browser (served however you serve it now — `python3 -m http.server` from `web/`, or via the Jetson hostname). Click a camera. WHEP request fires; video should appear.

## What gets deleted (rough LOC)

| File | Lines deleted | Lines added |
|---|---|---|
| `include/CameraPipeline.hpp` | ~20 | ~3 |
| `src/CameraPipeline.cpp` | ~150 | ~5 |
| `include/CameraManager.hpp` | ~6 | 0 |
| `src/CameraManager.cpp` | ~30 | 0 |
| `src/main.cpp` | ~30 | 0 |
| `web/index.html` | ~30 | ~25 |
| `mediamtx.yml` (new) | — | ~25 |
| `run.sh` (new) | — | ~15 |

Net ~250 LOC deleted, ~75 added. The whole ICE message routing apparatus goes away.

## Verification checklist (in branch, before declaring done)

1. `cmake --build build` succeeds with no `gst-webrtc` includes referenced.
2. `./run.sh` starts both MediaMTX and the backend; log shows MediaMTX bound to 8554 and 8889.
3. Backend logs show pipelines reaching PLAYING when a camera is enabled.
4. `curl -s http://localhost:9997/v3/paths/list | jq` (MediaMTX API) shows each enabled camera as a path with `ready: true`.
5. Browser GUI: clicking a camera renders video within 2-3 seconds.
6. **Offline test**: disconnect WAN, restart everything, repeat #5. Streams must come up. *This is the actual goal of this branch.*
7. Latency feels reasonable (eyeball <300ms glass-to-glass).
8. Stats display in GUI still moves (fps/bitrate come from C++ side, unchanged).

## Risks / things to confirm in flight

- **`rtspclientsink` availability** on the Jetson. It's part of `gstreamer1.0-rtsp` plugins package. `gst-inspect-1.0 rtspclientsink` should print details. If missing, `sudo apt install gstreamer1.0-rtsp` (or equivalent for L4T).
- **MediaMTX ARM64 build** — verified to exist (`linux_arm64v8`). No need to compile from source.
- **Authentication config schema** in MediaMTX moves between versions. Pin a specific version (e.g., `v1.9.x`) and copy the matching config from its docs.
- **NVENC + rtspclientsink interaction** — should be transparent (just a different sink), but worth confirming buffer flow with `GST_DEBUG=*:3` on the first run.
- **WebRTC over loopback in MediaMTX** — MediaMTX gathers local candidates fine without any STUN. Make sure `webrtcLocalUDPAddress: :8189` (or whatever) is open in any firewall on the Jetson. Currently `iptables` is clean per `netcheck.md`, so this is moot, but a future firewall could break it.
- **CORS** for the WHEP `fetch()` from browser — MediaMTX sets permissive CORS by default. Confirm with browser devtools if a request gets blocked.

## Rollback

Branch is `mediamtx-whep`. Original `webrtcbin` code stays intact on `main` until we merge.

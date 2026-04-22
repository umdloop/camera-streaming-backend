# camera-streaming-backend

WebRTC camera streaming backend using GStreamer and WebSockets.

## Dependencies

### Linux (Ubuntu/Debian)

```bash
sudo apt install \
    cmake ninja-build pkg-config \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    gstreamer1.0-nice \
    libwebsockets-dev \
    libssl-dev
```
No idea if those are right.

### macOS via brew install

```bash
brew install cmake ninja pkg-config \
    gstreamer \
    libwebsockets \
    openssl
```

## Build

```bash
cmake -B build -G Ninja
cmake --build build
```

## Run

```bash
./build/camera-stream [--ws-port <port>]
```

Serve the web client from the repo root and open `http://localhost:8000/web/`:

```bash
python3 -m http.server 8000
```

## Ubuntu Chrome/Chromium note

If the page connects but no video appears on Ubuntu/Linux Chrome-family browsers, the browser may be hiding its local ICE address behind an mDNS `.local` hostname that `libnice` does not use successfully in this setup. Launch the browser with mDNS host ICE masking disabled:

Chrome:

```bash
google-chrome --disable-features=WebRtcHideLocalIpsWithMdns
```

Chromium:

```bash
chromium --disable-features=WebRtcHideLocalIpsWithMdns
```

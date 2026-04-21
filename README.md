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

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

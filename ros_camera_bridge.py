#!/usr/bin/env python3
"""
ros_camera_bridge.py

Connects to the existing rosbridge WebSocket server, subscribes to a ROS
sensor_msgs/Image topic, and publishes the frames to MediaMTX via RTSP
using a GStreamer appsrc pipeline.

No ROS2 install required — uses the existing rosbridge WS on port 9090.

Usage (invoked by the C++ backend automatically):
  python3 ros_camera_bridge.py \
    --topic /cameras/cam0/image_raw \
    --stream-name camera_0 \
    [--width 640] [--height 480] [--fps 30] [--bitrate 500000] \
    [--rosbridge-port 9090]
"""

import argparse
import asyncio
import base64
import json
import signal
import sys
import threading

import numpy as np

import gi
gi.require_version("Gst", "1.0")
from gi.repository import Gst

import websockets


class RosCameraBridge:
    def __init__(self, args):
        self.args = args
        self.appsrc = None
        self.pipeline = None
        self.running = True
        self._pts = 0
        self._frame_duration_ns = int(1e9 / args.fps)

    def setup_gstreamer(self):
        Gst.init(None)
        bitrate_kbps = self.args.bitrate // 1000
        caps = (
            f"video/x-raw,format=BGR,"
            f"width={self.args.width},height={self.args.height},"
            f"framerate={self.args.fps}/1"
        )
        pipeline_str = (
            f"appsrc name=src format=time is-live=true block=false "
            f"caps=\"{caps}\" "
            f"! videoconvert "
            f"! x264enc tune=zerolatency bitrate={bitrate_kbps} "
            f"speed-preset=ultrafast key-int-max=30 "
            f"! h264parse "
            f"! video/x-h264,stream-format=byte-stream,alignment=au "
            f"! rtspclientsink name=sink protocols=tcp latency=0 "
            f"location=rtsp://127.0.0.1:8554/{self.args.stream_name}"
        )
        self.pipeline = Gst.parse_launch(pipeline_str)
        self.appsrc = self.pipeline.get_by_name("src")
        ret = self.pipeline.set_state(Gst.State.PLAYING)
        if ret == Gst.StateChangeReturn.FAILURE:
            print("[bridge] GStreamer pipeline failed to start", file=sys.stderr)
            sys.exit(1)
        print(
            f"[bridge] GStreamer pipeline started: "
            f"appsrc → x264 → rtsp://127.0.0.1:8554/{self.args.stream_name}",
            file=sys.stderr,
        )

    def push_frame(self, image_msg: dict):
        if self.appsrc is None or not self.running:
            return
        try:
            raw = base64.b64decode(image_msg["data"])
            h = image_msg["height"]
            w = image_msg["width"]
            encoding = image_msg["encoding"]

            arr = np.frombuffer(raw, dtype=np.uint8)
            if encoding == "bgr8":
                frame = arr.reshape(h, w, 3)
            elif encoding == "rgb8":
                frame = arr.reshape(h, w, 3)[:, :, ::-1]          # RGB → BGR
            elif encoding in ("bgra8", "8UC4"):
                frame = arr.reshape(h, w, 4)[:, :, :3]             # BGRA → BGR (drop alpha)
            elif encoding == "rgba8":
                frame = arr.reshape(h, w, 4)[:, :, [2, 1, 0]]     # RGBA → BGR
            elif encoding == "mono8":
                gray = arr.reshape(h, w)
                frame = np.stack([gray, gray, gray], axis=2)
            else:
                print(f"[bridge] unsupported encoding: {encoding}", file=sys.stderr)
                return

            # Resize if the topic resolution differs from the configured output size
            if w != self.args.width or h != self.args.height:
                import cv2
                frame = cv2.resize(frame, (self.args.width, self.args.height))

            buf = Gst.Buffer.new_wrapped(bytes(frame))
            buf.pts = self._pts
            buf.duration = self._frame_duration_ns
            self._pts += self._frame_duration_ns

            self.appsrc.emit("push-buffer", buf)
        except Exception as exc:
            print(f"[bridge] push_frame error: {exc}", file=sys.stderr)

    async def run(self):
        uri = f"ws://127.0.0.1:{self.args.rosbridge_port}"
        reconnect_delay = 1.0

        while self.running:
            try:
                async with websockets.connect(uri, max_size=10 * 1024 * 1024) as ws:
                    reconnect_delay = 1.0
                    sub_msg = json.dumps({
                        "op": "subscribe",
                        "topic": self.args.topic,
                        "type": "sensor_msgs/Image",
                        "queue_length": 1,
                        "throttle_rate": 0,
                        "compression": "none",
                    })
                    await ws.send(sub_msg)
                    print(
                        f"[bridge] subscribed to {self.args.topic} via rosbridge {uri}",
                        file=sys.stderr,
                    )
                    while self.running:
                        try:
                            raw = await asyncio.wait_for(ws.recv(), timeout=5.0)
                        except asyncio.TimeoutError:
                            continue
                        msg = json.loads(raw)
                        if msg.get("op") == "publish" and msg.get("topic") == self.args.topic:
                            self.push_frame(msg["msg"])
            except (websockets.ConnectionClosed, ConnectionRefusedError, OSError) as exc:
                if not self.running:
                    break
                print(
                    f"[bridge] rosbridge connection lost ({exc}), "
                    f"retrying in {reconnect_delay:.0f}s",
                    file=sys.stderr,
                )
                await asyncio.sleep(reconnect_delay)
                reconnect_delay = min(reconnect_delay * 2, 10.0)

    def stop(self):
        self.running = False
        if self.pipeline:
            self.pipeline.set_state(Gst.State.NULL)


def main():
    parser = argparse.ArgumentParser(description="ROS Image → MediaMTX RTSP bridge via rosbridge")
    parser.add_argument("--topic",          required=True,  help="ROS Image topic")
    parser.add_argument("--stream-name",    required=True,  dest="stream_name", help="MediaMTX RTSP path")
    parser.add_argument("--width",          type=int, default=640)
    parser.add_argument("--height",         type=int, default=480)
    parser.add_argument("--fps",            type=int, default=30)
    parser.add_argument("--bitrate",        type=int, default=500000, help="Bitrate in bits/s")
    parser.add_argument("--rosbridge-port", type=int, default=9090,   dest="rosbridge_port")
    args = parser.parse_args()

    bridge = RosCameraBridge(args)
    bridge.setup_gstreamer()

    loop = asyncio.new_event_loop()

    def handle_signal(sig, frame):
        bridge.stop()
        loop.call_soon_threadsafe(loop.stop)

    signal.signal(signal.SIGTERM, handle_signal)
    signal.signal(signal.SIGINT, handle_signal)

    try:
        loop.run_until_complete(bridge.run())
    finally:
        bridge.stop()
        loop.close()


if __name__ == "__main__":
    main()

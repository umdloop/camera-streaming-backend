#include <csignal>
#include <cstdlib>
#include <gst/gst.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include "CameraManager.hpp"
#include "WsServer.hpp"

using json = nlohmann::json;

static constexpr int kDefaultWsPort = 8081;

static const char* kConfigPath = "cameras.json";

static GMainLoop* gLoop = nullptr;

static void printUsage(const char* prog) {
    std::cerr << "Usage: " << prog << " [--ws-port <port>]\n"
              << "  --ws-port  WebSocket signaling port (default " << kDefaultWsPort << ")\n";
}

int main(int argc, char* argv[]) {
    int wsPort = kDefaultWsPort;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--ws-port" && i + 1 < argc) {
            int val = std::atoi(argv[++i]);
            if (val <= 0 || val > 65535) {
                std::cerr << "Invalid port: " << argv[i] << "\n";
                 return 1;
           }
            wsPort = val;
        } else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    gst_init(&argc, &argv);

    CameraManager manager;
    WsServer      ws;

    auto sendState = [&]() {
        ws.sendMessage(manager.buildStateJson());
    };

    manager.setOfferCallback([&](const std::string& id, const std::string& sdp) {
        ws.sendMessage(json{{"type","offer"},{"id",id},{"sdp",sdp}}.dump());
    });
    manager.setIceCallback([&](const std::string& id, const std::string& candidate, int mline) {
        ws.sendMessage(json{{"type","ice"},{"id",id},{"candidate",candidate},{"sdpMLineIndex",mline}}.dump());
    });

    manager.loadConfigs(kConfigPath);
    manager.discoverCameras();
    manager.saveConfigs(kConfigPath);

    ws.setOnConnectCallback(sendState);

    ws.setOnMessageCallback([&](const std::string& raw) {
        try {
            auto msg  = json::parse(raw);
            auto type = msg["type"].get<std::string>();

            if (type == "answer") {
                manager.setRemoteAnswer(msg["id"], msg["sdp"]);
            } else if (type == "ice") {
                manager.addIceCandidate(msg["id"], msg["candidate"], msg["sdpMLineIndex"]);
            } else if (type == "enable") {
                manager.enableCamera(msg["camera_id"]);
                sendState();
            } else if (type == "disable") {
                manager.disableCamera(msg["camera_id"]);
                sendState();
            } else if (type == "set_config") {
                manager.applyConfigPatch(msg["camera_id"], msg["config"]);
                manager.saveConfigs(kConfigPath);
                sendState();
            } else if (type == "rename") {
                manager.renameCamera(msg["camera_id"], msg["name"]);
                manager.saveConfigs(kConfigPath);
                sendState();
            }
        } catch (const std::exception& e) {
            std::cerr << "ws message error: " << e.what() << std::endl;
        }
    });

    if (!ws.start(wsPort)) {
        std::cerr << "Failed to start WebSocket server" << std::endl;
        return 1;
    }


    std::thread wsThread([&]() {
        while (ws.poll()) {}
    });

    struct StatsCtx { CameraManager* m; WsServer* s; } statsCtx{&manager, &ws};
    g_timeout_add(500, [](gpointer data) -> gboolean {
        auto& ctx = *static_cast<StatsCtx*>(data);
        for (const auto& [id, cfg] : ctx.m->getConfigs()) {
            if (!ctx.m->isEnabled(id)) continue;
            auto s = ctx.m->getCameraStats(id);
            ctx.s->sendMessage(json{
                {"type",      "stats"},
                {"camera_id", id},
                {"fps",       s.fps},
                {"bitrate",   s.bitrate},
            }.dump());
        }
        return TRUE;
    }, &statsCtx);

    gLoop = g_main_loop_new(nullptr, FALSE);

    signal(SIGINT,  [](int) { if (gLoop) g_main_loop_quit(gLoop); });
    signal(SIGTERM, [](int) { if (gLoop) g_main_loop_quit(gLoop); });

    g_main_loop_run(gLoop);
    g_main_loop_unref(gLoop);

    ws.stop();
    wsThread.join();
    return 0;
}

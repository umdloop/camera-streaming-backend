#include "WsServer.hpp"
#include <cstring>
#include <iostream>
#include <vector>

static int callback_ws(struct lws* wsi, enum lws_callback_reasons reason, void* user, void* in, size_t len) {
    auto* server = reinterpret_cast<WsServer*>(lws_context_user(lws_get_context(wsi)));
    return server ? server->onWsCallback(wsi, reason, in, len) : 0;
}

static struct lws_protocols protocols[] = {
    { "webrtc-protocol", callback_ws, 0, 65536 },
    { nullptr, nullptr, 0, 0 }
};

WsServer::WsServer() {}

WsServer::~WsServer() {
    if (context_) lws_context_destroy(context_);
}

bool WsServer::start(int port) {
    lws_context_creation_info info{};
    info.port      = port;
    info.protocols = protocols;
    info.user      = this;

    context_ = lws_create_context(&info);
    if (!context_) {
        std::cerr << "lws init failed" << std::endl;
        return false;
    }
    std::cout << "WebSocket server started on port " << port << std::endl;
    return true;
}

bool WsServer::poll() {
    if (!running_ || !context_) return false;
    lws_service(context_, 50);
    return running_.load();
}

void WsServer::stop() {
    running_ = false;
    if (context_) lws_cancel_service(context_);
}

void WsServer::sendMessage(const std::string& message) {
    {
        std::lock_guard<std::mutex> lock(queueMutex_);
        messageQueue_.push(message);
    }
    if (context_) lws_cancel_service(context_);
}

int WsServer::onWsCallback(lws* wsi, lws_callback_reasons reason, void* in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_ESTABLISHED:
            client_wsi_ = wsi;
            std::cout << "Client connected" << std::endl;
            if (onConnect_) onConnect_();
            lws_callback_on_writable(wsi);
            break;

        case LWS_CALLBACK_CLOSED:
            if (client_wsi_ == wsi) {
                client_wsi_ = nullptr;
                std::cout << "Client disconnected" << std::endl;
            }
            break;

        case LWS_CALLBACK_RECEIVE:
            if (onMessage_ && in)
                onMessage_(std::string(static_cast<char*>(in), len));
            break;

        case LWS_CALLBACK_EVENT_WAIT_CANCELLED:
            if (client_wsi_) lws_callback_on_writable(client_wsi_);
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE: {
            std::lock_guard<std::mutex> lock(queueMutex_);
            while (!messageQueue_.empty()) {
                std::string msg = messageQueue_.front();
                messageQueue_.pop();
                std::vector<unsigned char> buf(LWS_PRE + msg.size());
                memcpy(&buf[LWS_PRE], msg.c_str(), msg.size());
                lws_write(wsi, &buf[LWS_PRE], msg.size(), LWS_WRITE_TEXT);
            }
            break;
        }

        default:
            break;
    }
    return 0;
}

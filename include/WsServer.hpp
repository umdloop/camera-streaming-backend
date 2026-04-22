#pragma once

#include <libwebsockets.h>
#include <atomic>
#include <functional>
#include <mutex>
#include <queue>
#include <string>

class WsServer {
public:
    using MessageCallback = std::function<void(const std::string& message)>;
    using ConnectCallback = std::function<void()>;

    WsServer();
    ~WsServer();

    bool start(int port);
    bool poll();
    void stop();
    void sendMessage(const std::string& message);

    void setOnMessageCallback(MessageCallback cb) { onMessage_ = cb; }
    void setOnConnectCallback(ConnectCallback cb)  { onConnect_ = cb; }

    int onWsCallback(lws* wsi, lws_callback_reasons reason, void* in, size_t len);

private:
    lws_context*    context_    = nullptr;
    lws*            client_wsi_ = nullptr;
    std::atomic<bool> running_{true};
    MessageCallback onMessage_;
    ConnectCallback onConnect_;
    std::string     receiveBuffer_;

    std::mutex             queueMutex_;
    std::queue<std::string> messageQueue_;
};

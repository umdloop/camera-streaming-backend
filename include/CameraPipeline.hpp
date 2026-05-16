#pragma once

#include <gst/gst.h>
#include <atomic>
#include <functional>
#include <mutex>
#include <string>

#include "CameraConfig.hpp"

struct PipelineStats {
    double fps     = 0.0;
    int    bitrate = 0;
};

class CameraPipeline {
public:
    using OnErrorCallback = std::function<void(const std::string& message)>;

    CameraPipeline(const CameraConfig& config, const std::string& streamName);
    ~CameraPipeline();

    bool start();
    void stop();

    void setOnErrorCallback(OnErrorCallback cb) { onError_ = cb; }

    bool hasFailed() const { return failed_.load(); }
    std::string getLastError() const;

    PipelineStats getStats();

private:
    CameraConfig config_;
    std::string  streamName_;
    GstElement*  pipeline_   = nullptr;
    guint        busWatchId_ = 0;

    std::atomic<int>       frameCount_{0};
    std::atomic<long long> byteCount_{0};
    std::atomic<long long> lastStatsMs_{0};
    std::atomic<bool>      failed_{false};
    std::string            lastError_;
    mutable std::mutex     errorMutex_;

    OnErrorCallback onError_;

    static GstPadProbeReturn statsProbe(GstPad* pad, GstPadProbeInfo* info, gpointer user_data);
    static gboolean onBusMessage(GstBus* bus, GstMessage* message, gpointer user_data);
};

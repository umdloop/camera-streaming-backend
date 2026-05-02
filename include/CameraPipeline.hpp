#pragma once

#include <gst/gst.h>
#include <gst/webrtc/webrtc.h>
#include <atomic>
#include <chrono>
#include <functional>
#include <string>

#include "CameraConfig.hpp"

struct PipelineStats {
    double fps     = 0.0;
    int    bitrate = 0;
};

class CameraPipeline {
public:
    using OnIceCandidateCallback = std::function<void(const std::string& candidate, int sdpMLineIndex)>;
    using OnOfferCreatedCallback = std::function<void(const std::string& sdp)>;

    CameraPipeline(const CameraConfig& config, std::string stunServer = {});
    ~CameraPipeline();

    bool start();
    void stop();

    void setRemoteAnswer(const std::string& sdp);
    void addIceCandidate(const std::string& candidate, int sdpMLineIndex);

    void setOnIceCandidateCallback(OnIceCandidateCallback cb) { onIceCandidate_ = cb; }
    void setOnOfferCreatedCallback(OnOfferCreatedCallback cb) { onOfferCreated_ = cb; }

    PipelineStats getStats();

    static void onOfferCreated(GstPromise* promise, gpointer user_data);

private:
    CameraConfig config_;
    std::string  stunServer_;
    GstElement* pipeline_  = nullptr;
    GstElement* webrtcbin_ = nullptr;

    std::atomic<int>       frameCount_{0};
    std::atomic<long long> byteCount_{0};
    std::atomic<long long> lastStatsMs_{0};
    std::atomic<bool>      offerScheduled_{false};

    OnIceCandidateCallback onIceCandidate_;
    OnOfferCreatedCallback onOfferCreated_;

    static GstPadProbeReturn statsProbe(GstPad* pad, GstPadProbeInfo* info, gpointer user_data);
    static void onNegotiationNeeded(GstElement* webrtcbin, gpointer user_data);
    static void onIceCandidate(GstElement* webrtcbin, guint mlineindex, gchar* candidate, gpointer user_data);
};

#include "CameraPipeline.hpp"
#include "PlatformDetect.hpp"
#include <chrono>
#include <gst/sdp/gstsdpmessage.h>
#include <iostream>
#include <sys/time.h>

static std::string timestamp() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    struct tm* t = localtime(&tv.tv_sec);
    char buf[16];
    strftime(buf, sizeof(buf), "%H:%M:%S", t);
    return std::string(buf) + "." + std::to_string(tv.tv_usec / 1000);
}

static std::string buildPipelineString(const CameraConfig& cfg, const PlatformSpecifics& specs) {
    const bool isMjpg = (cfg.format == "MJPG");

    std::string src;

    if (specs.source == "videotestsrc") {
        src = "videotestsrc name=src"
              " ! video/x-raw,width=640,height=480,framerate=30/1"
              " ! timeoverlay";
    } else if (specs.source == "v4l2src") {
        src = "v4l2src name=src device=" + cfg.devicePath + " !";
        if (isMjpg) {
            src += " image/jpeg"
                   ",width="  + std::to_string(cfg.width) +
                   ",height=" + std::to_string(cfg.height);
        } else {
            src += " video/x-raw";
            if (!cfg.format.empty()) src += ",format=" + cfg.format;
            src += ",width="  + std::to_string(cfg.width) +
                   ",height=" + std::to_string(cfg.height);
        }
        if (isMjpg) src += " ! jpegdec";
        src += " ! videorate ! video/x-raw,framerate=" + std::to_string(cfg.fps) + "/1";
    } else {
        src = "avfvideosrc name=src device-index=" + cfg.devicePath +
              " ! video/x-raw"
              ",width="     + std::to_string(cfg.width) +
              ",height="    + std::to_string(cfg.height) +
              ",framerate=" + std::to_string(cfg.fps) + "/1";
    }

    std::string enc = specs.encoder;
    if (specs.encoder == "vtenc_h264") {
        enc += " realtime=true bitrate=" + std::to_string(cfg.bitrate / 1000);
    } else if (specs.encoder == "nvv4l2h264enc") {
        // NVIDIA encoder expects bits/sec
        enc += " insert-sps-pps=true idrinterval=30 bitrate=" + std::to_string(cfg.bitrate);
    } else {
        // x264enc expects kbits/sec
        enc += " tune=zerolatency bitrate=" + std::to_string(cfg.bitrate / 1000) + " speed-preset=ultrafast key-int-max=30";
    }

    return src +
           " ! videoconvert" +
           " ! " + specs.converter +
           " ! " + enc +
           " ! h264parse" +
           " ! video/x-h264,profile=baseline,stream-format=byte-stream,alignment=au"
           " ! rtph264pay name=pay0 config-interval=1 aggregate-mode=zero-latency"
           " ! application/x-rtp,media=video,encoding-name=H264,payload=96,packetization-mode=1"
           " ! webrtcbin name=webrtcbin bundle-policy=max-bundle";
}

// ── Negotiation Helpers ───────────────────────────────────────────────────────

struct NegotiationCtx {
    GstElement*     webrtcbin;
    CameraPipeline* pipeline;
};

struct SdpCtx {
    GstElement* webrtcbin;
    std::string sdp;
};

struct IceCtx {
    GstElement* webrtcbin;
    std::string candidate;
    int mline;
};

static gboolean doSetRemoteAnswer(gpointer data) {
    auto* ctx = static_cast<SdpCtx*>(data);
    GstSDPMessage* sdpMsg = nullptr;
    gst_sdp_message_new(&sdpMsg);
    if (gst_sdp_message_parse_buffer(reinterpret_cast<const guint8*>(ctx->sdp.c_str()), ctx->sdp.size(), sdpMsg) == GST_SDP_OK) {
        GstWebRTCSessionDescription* answer =
            gst_webrtc_session_description_new(GST_WEBRTC_SDP_TYPE_ANSWER, sdpMsg);
        GstPromise* promise = gst_promise_new();
        g_signal_emit_by_name(ctx->webrtcbin, "set-remote-description", answer, promise);
        gst_promise_unref(promise);
        gst_webrtc_session_description_free(answer);
    } else {
        gst_sdp_message_free(sdpMsg);
    }
    delete ctx;
    return G_SOURCE_REMOVE;
}

static gboolean doAddIceCandidate(gpointer data) {
    auto* ctx = static_cast<IceCtx*>(data);
    g_signal_emit_by_name(ctx->webrtcbin, "add-ice-candidate", ctx->mline, ctx->candidate.c_str());
    delete ctx;
    return G_SOURCE_REMOVE;
}

static gboolean doCreateOffer(gpointer data) {
    auto* ctx = static_cast<NegotiationCtx*>(data);
    std::cout << "[" << timestamp() << "] Creating offer on main loop" << std::endl;
    GstPromise* promise = gst_promise_new_with_change_func(CameraPipeline::onOfferCreated, ctx->pipeline, nullptr);
    g_signal_emit_by_name(ctx->webrtcbin, "create-offer", nullptr, promise);
    delete ctx;
    return G_SOURCE_REMOVE;
}

// ── CameraPipeline ────────────────────────────────────────────────────────────

CameraPipeline::CameraPipeline(const CameraConfig& config) : config_(config) {}

CameraPipeline::~CameraPipeline() {
    stop();
}

bool CameraPipeline::start() {
    if (pipeline_) return true;

    auto specs = PlatformDetect::getPlatformSpecifics();
    if (config_.devicePath == "test") specs.source = "videotestsrc";

    std::string pipelineStr = buildPipelineString(config_, specs);
    std::cout << "[" << timestamp() << "] Starting pipeline: " << pipelineStr << std::endl;

    GError* error = nullptr;
    pipeline_ = gst_parse_launch(pipelineStr.c_str(), &error);
    if (error) {
        std::cerr << "[" << timestamp() << "] Pipeline parse error: " << error->message << std::endl;
        g_error_free(error);
        return false;
    }

    webrtcbin_ = gst_bin_get_by_name(GST_BIN(pipeline_), "webrtcbin");
    if (!webrtcbin_) {
        std::cerr << "webrtcbin element not found" << std::endl;
        stop();
        return false;
    }

    g_signal_connect(webrtcbin_, "on-negotiation-needed", G_CALLBACK(onNegotiationNeeded), this);
    g_signal_connect(webrtcbin_, "on-ice-candidate",      G_CALLBACK(onIceCandidate),      this);

    GstElement* pay = gst_bin_get_by_name(GST_BIN(pipeline_), "pay0");
    if (pay) {
        GstPad* pad = gst_element_get_static_pad(pay, "src");
        if (pad) {
            frameCount_.store(0);
            byteCount_.store(0);
            lastStatsMs_.store(std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count());
            gst_pad_add_probe(pad, GST_PAD_PROBE_TYPE_BUFFER, statsProbe, this, nullptr);
            gst_object_unref(pad);
        }
        gst_object_unref(pay);
    }

    if (config_.exposure >= 0) {
        GstElement* src = gst_bin_get_by_name(GST_BIN(pipeline_), "src");
        if (src) {
            if (g_object_class_find_property(G_OBJECT_GET_CLASS(src), "extra-controls")) {
                GstStructure* ctrls = gst_structure_new("controls",
                    "exposure_auto",     G_TYPE_INT, 1,
                    "exposure_absolute", G_TYPE_INT, config_.exposure,
                    nullptr);
                g_object_set(src, "extra-controls", ctrls, nullptr);
                gst_structure_free(ctrls);
            }
            gst_object_unref(src);
        }
    }

    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "[" << timestamp() << "] Failed to set pipeline to PLAYING" << std::endl;
        stop();
        return false;
    }
    std::cout << "[" << timestamp() << "] Pipeline state change: "
              << gst_element_state_change_return_get_name(ret) << std::endl;

    // Fallback: explicitly schedule offer creation on the GLib main loop.
    // on-negotiation-needed may not fire reliably when set_state is called
    // from a non-main thread (e.g., the WebSocket thread).
    // offerScheduled_ prevents a double-offer if on-negotiation-needed also fires.
    bool expected = false;
    if (offerScheduled_.compare_exchange_strong(expected, true))
        g_idle_add(doCreateOffer, new NegotiationCtx{webrtcbin_, this});

    return true;
}

void CameraPipeline::stop() {
    offerScheduled_.store(false);
    if (webrtcbin_) {
        gst_element_set_state(webrtcbin_, GST_STATE_NULL);
        gst_object_unref(webrtcbin_);
        webrtcbin_ = nullptr;
    }
    if (pipeline_) {
        std::cout << "[" << timestamp() << "] Stopping pipeline" << std::endl;
        gst_element_set_state(pipeline_, GST_STATE_NULL);
        gst_object_unref(pipeline_);
        pipeline_ = nullptr;
    }
}

void CameraPipeline::setRemoteAnswer(const std::string& sdp) {
    if (!webrtcbin_) return;
    g_main_context_invoke(nullptr, doSetRemoteAnswer, new SdpCtx{webrtcbin_, sdp});
}

void CameraPipeline::addIceCandidate(const std::string& candidate, int sdpMLineIndex) {
    if (!webrtcbin_) return;
    g_main_context_invoke(nullptr, doAddIceCandidate, new IceCtx{webrtcbin_, candidate, sdpMLineIndex});
}

PipelineStats CameraPipeline::getStats() {
    long long nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
    long long lastMs = lastStatsMs_.exchange(nowMs);
    int       frames = frameCount_.exchange(0);
    long long bytes  = byteCount_.exchange(0);
    double elapsed   = (nowMs - lastMs) / 1000.0;
    PipelineStats s;
    if (elapsed > 0.01) {
        s.fps     = frames / elapsed;
        s.bitrate = static_cast<int>(bytes * 8 / elapsed);
    }
    return s;
}

GstPadProbeReturn CameraPipeline::statsProbe(GstPad*, GstPadProbeInfo* info, gpointer user_data) {
    auto* self = static_cast<CameraPipeline*>(user_data);
    if (GstBuffer* buf = GST_PAD_PROBE_INFO_BUFFER(info)) {
        self->frameCount_.fetch_add(1, std::memory_order_relaxed);
        self->byteCount_.fetch_add(static_cast<long long>(gst_buffer_get_size(buf)),
                                   std::memory_order_relaxed);
    }
    return GST_PAD_PROBE_OK;
}

void CameraPipeline::onNegotiationNeeded(GstElement* webrtcbin, gpointer user_data) {
    auto* self = static_cast<CameraPipeline*>(user_data);
    std::cout << "[" << timestamp() << "] on-negotiation-needed fired" << std::endl;
    bool expected = false;
    if (self->offerScheduled_.compare_exchange_strong(expected, true))
        g_idle_add(doCreateOffer, new NegotiationCtx{webrtcbin, self});
}

void CameraPipeline::onIceCandidate(GstElement*, guint mlineindex, gchar* candidate, gpointer user_data) {
    auto* self = static_cast<CameraPipeline*>(user_data);
    if (self->onIceCandidate_) self->onIceCandidate_(candidate, mlineindex);
}

void CameraPipeline::onOfferCreated(GstPromise* promise, gpointer user_data) {
    std::cout << "[" << timestamp() << "] Offer created" << std::endl;
    auto* self = static_cast<CameraPipeline*>(user_data);

    const GstStructure* reply = gst_promise_get_reply(promise);
    GstWebRTCSessionDescription* offer = nullptr;
    gst_structure_get(reply, "offer", GST_TYPE_WEBRTC_SESSION_DESCRIPTION, &offer, nullptr);
    gst_promise_unref(promise);

    if (offer) {
        GstPromise* localDescPromise = gst_promise_new();
        g_signal_emit_by_name(self->webrtcbin_, "set-local-description", offer, localDescPromise);
        gst_promise_unref(localDescPromise);

        if (self->onOfferCreated_) {
            gchar* sdpStr = gst_sdp_message_as_text(offer->sdp);
            self->onOfferCreated_(sdpStr);
            g_free(sdpStr);
        }
        gst_webrtc_session_description_free(offer);
    }
}

#include "CameraManager.hpp"
#include <algorithm>
#include <fstream>
#include <gst/gst.h>
#include <iostream>

using json = nlohmann::json;

static int extractMaxFps(const GValue* v) {
    if (GST_VALUE_HOLDS_FRACTION(v)) {
        int n = gst_value_get_fraction_numerator(v);
        int d = gst_value_get_fraction_denominator(v);
        return d > 0 ? n / d : 0;
    }
    if (GST_VALUE_HOLDS_LIST(v)) {
        int best = 0;
        guint sz = gst_value_list_get_size(v);
        for (guint i = 0; i < sz; ++i) {
            const GValue* item = gst_value_list_get_value(v, i);
            if (GST_VALUE_HOLDS_FRACTION(item)) {
                int n = gst_value_get_fraction_numerator(item);
                int d = gst_value_get_fraction_denominator(item);
                if (d > 0) best = std::max(best, n / d);
            }
        }
        return best;
    }
    if (GST_VALUE_HOLDS_FRACTION_RANGE(v)) {
        const GValue* hi = gst_value_get_fraction_range_max(v);
        if (hi && GST_VALUE_HOLDS_FRACTION(hi)) {
            int n = gst_value_get_fraction_numerator(hi);
            int d = gst_value_get_fraction_denominator(hi);
            return d > 0 ? n / d : 0;
        }
    }
    return 0;
}

static std::vector<CameraMode> parseCaps(GstCaps* caps) {
    std::vector<CameraMode> modes;
    if (!caps || gst_caps_is_any(caps) || gst_caps_is_empty(caps)) return modes;

    guint n = gst_caps_get_size(caps);
    for (guint i = 0; i < n; ++i) {
        GstStructure* s    = gst_caps_get_structure(caps, i);
        const gchar*  name = gst_structure_get_name(s);

        CameraMode mode;
        if (g_str_equal(name, "image/jpeg")) {
            mode.format = "MJPG";
        } else if (g_str_equal(name, "video/x-raw")) {
            const gchar* fmt = gst_structure_get_string(s, "format");
            if (!fmt) continue;
            mode.format = fmt;
        } else {
            continue;
        }

        if (!gst_structure_get_int(s, "width",  &mode.width))  continue;
        if (!gst_structure_get_int(s, "height", &mode.height)) continue;

        const GValue* fpsVal = gst_structure_get_value(s, "framerate");
        if (!fpsVal) continue;
        mode.maxFps = extractMaxFps(fpsVal);
        if (mode.maxFps <= 0) continue;

        auto it = std::find_if(modes.begin(), modes.end(), [&](const CameraMode& m) {
            return m.format == mode.format && m.width == mode.width && m.height == mode.height;
        });
        if (it != modes.end()) {
            it->maxFps = std::max(it->maxFps, mode.maxFps);
        } else {
            modes.push_back(mode);
        }
    }

    std::sort(modes.begin(), modes.end(), [](const CameraMode& a, const CameraMode& b) {
        int pa = a.width * a.height, pb = b.width * b.height;
        if (pa != pb) return pa > pb;
        if (a.format != b.format) return a.format < b.format;
        return a.maxFps > b.maxFps;
    });

    return modes;
}


void CameraManager::loadConfigs(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) return;

    try {
        auto j = json::parse(f);
        for (auto& [id, obj] : j["cameras"].items()) {
            CameraConfig cfg;
            cfg.devicePath = obj["devicePath"];
            cfg.name       = obj.value("name",     "");
            cfg.format     = obj.value("format",   "");
            cfg.width      = obj.value("width",    1280);
            cfg.height     = obj.value("height",   720);
            cfg.fps        = obj.value("fps",      30);
            cfg.bitrate    = obj.value("bitrate",  2000000);
            cfg.exposure   = obj.value("exposure", -1);
            configs_[id]   = cfg;
        }
    } catch (const std::exception& e) {
        std::cerr << "loadConfigs: " << e.what() << std::endl;
    }
}

void CameraManager::saveConfigs(const std::string& path) const {
    json cameras = json::object();
    for (const auto& [id, cfg] : configs_) {
        cameras[id] = {
            {"devicePath", cfg.devicePath},
            {"name",       cfg.name},
            {"format",     cfg.format},
            {"width",      cfg.width},
            {"height",     cfg.height},
            {"fps",        cfg.fps},
            {"bitrate",    cfg.bitrate},
            {"exposure",   cfg.exposure},
        };
    }
    std::ofstream f(path);
    f << json{{"cameras", cameras}}.dump(2) << "\n";
}

void CameraManager::discoverCameras() {
    int nextId = 0;

    auto pathExists = [&](const std::string& p) {
        for (const auto& [_, cfg] : configs_)
            if (cfg.devicePath == p) return true;
        return false;
    };

    auto generateName = [&]() {
        std::string name;
        do { name = "camera_" + std::to_string(nextId++); }
        while (configs_.count(name));
        return name;
    };

    GstDeviceMonitor* monitor = gst_device_monitor_new();
    gst_device_monitor_add_filter(monitor, "Video/Source", nullptr);

    if (!gst_device_monitor_start(monitor)) {
        std::cerr << "discoverCameras: GstDeviceMonitor failed to start" << std::endl;
        gst_object_unref(monitor);
        return;
    }

    GList* devices = gst_device_monitor_get_devices(monitor);
    std::cout << "discoverCameras: found " << g_list_length(devices) << " device(s)" << std::endl;

    gst_device_monitor_stop(monitor);

    int idx = 0;
    for (GList* l = devices; l; l = l->next, ++idx) {
        GstDevice* device = GST_DEVICE(l->data);

        gchar* displayName = gst_device_get_display_name(device);
        std::cout << "  [" << idx << "] " << (displayName ? displayName : "(null)") << std::endl;
        g_free(displayName);

        std::string devicePath;

        GstStructure* props = gst_device_get_properties(device);
        if (props) {
            const gchar* p = gst_structure_get_string(props, "device.path");
            if (p) devicePath = p;
            gst_structure_free(props);
        }

        if (devicePath.empty()) {
            GstElement* elem = gst_device_create_element(device, nullptr);
            if (elem) {
                gint devIdx = -1;
                g_object_get(elem, "device-index", &devIdx, nullptr);
                devicePath = std::to_string(devIdx >= 0 ? devIdx : idx);
                gst_element_set_state(elem, GST_STATE_NULL);
                gst_object_unref(elem);
            } else {
                devicePath = std::to_string(idx);
            }
        }

        if (!devicePath.empty()) {
            GstCaps* caps = gst_device_get_caps(device);
            capabilities_[devicePath] = parseCaps(caps);
            if (caps) gst_caps_unref(caps);
            std::cout << "    -> " << capabilities_[devicePath].size() << " mode(s) discovered" << std::endl;
        }

        if (devicePath.empty()) {
            std::cerr << "    -> could not determine device path, skipping" << std::endl;
        } else if (pathExists(devicePath)) {
            std::cout << "    -> already registered" << std::endl;
        } else {
            std::string name = generateName();
            std::cout << "    -> registered as \"" << name << "\" path=" << devicePath << std::endl;
            configs_[name].devicePath = devicePath;
        }
    }

    g_list_free_full(devices, gst_object_unref);
    gst_object_unref(monitor);
}

void CameraManager::enableCamera(const std::string& id) {
    auto it = configs_.find(id);
    if (it == configs_.end()) {
        std::cerr << "enableCamera: unknown id: " << id << std::endl;
        return;
    }

    if (pipelines_.count(id)) disableCamera(id);

    auto pipeline = std::make_unique<CameraPipeline>(it->second);

    if (onOffer_) {
        pipeline->setOnOfferCreatedCallback([this, id](const std::string& sdp) {
            onOffer_(id, sdp);
        });
    }
    if (onIce_) {
        pipeline->setOnIceCandidateCallback([this, id](const std::string& candidate, int mline) {
            onIce_(id, candidate, mline);
        });
    }

    if (pipeline->start()) {
        pipelines_[id] = std::move(pipeline);
        std::cout << "Camera enabled: " << id << std::endl;
    } else {
        std::cerr << "Failed to start pipeline for: " << id << std::endl;
    }
}

void CameraManager::disableCamera(const std::string& id) {
    pipelines_.erase(id);
    std::cout << "Camera disabled: " << id << std::endl;
}

bool CameraManager::renameCamera(const std::string& id, const std::string& newName) {
    if (id == newName || id.empty() || newName.empty()) return false;
    if (!configs_.count(id))     return false;
    if (configs_.count(newName)) return false;

    bool wasEnabled = pipelines_.count(id) > 0;
    if (wasEnabled) disableCamera(id);

    configs_[newName] = configs_[id];
    configs_.erase(id);

    if (wasEnabled) enableCamera(newName);
    return true;
}

bool CameraManager::updateConfig(const std::string& id, const CameraConfig& config) {
    if (!configs_.count(id)) return false;
    configs_[id] = config;
    if (pipelines_.count(id)) {
        disableCamera(id);
        enableCamera(id);
    }
    return true;
}

bool CameraManager::applyConfigPatch(const std::string& id, const json& patch) {
    auto it = configs_.find(id);
    if (it == configs_.end()) return false;
    CameraConfig& cfg = it->second;
    if (patch.contains("format"))   cfg.format   = patch["format"].get<std::string>();
    if (patch.contains("width"))    cfg.width    = patch["width"];
    if (patch.contains("height"))   cfg.height   = patch["height"];
    if (patch.contains("fps"))      cfg.fps      = patch["fps"];
    if (patch.contains("bitrate"))  cfg.bitrate  = patch["bitrate"];
    if (patch.contains("exposure")) cfg.exposure = patch["exposure"];
    if (pipelines_.count(id)) {
        disableCamera(id);
        enableCamera(id);
    }
    return true;
}

void CameraManager::setRemoteAnswer(const std::string& id, const std::string& sdp) {
    auto it = pipelines_.find(id);
    if (it != pipelines_.end()) it->second->setRemoteAnswer(sdp);
}

void CameraManager::addIceCandidate(const std::string& id, const std::string& candidate, int sdpMLineIndex) {
    auto it = pipelines_.find(id);
    if (it != pipelines_.end()) it->second->addIceCandidate(candidate, sdpMLineIndex);
}

std::string CameraManager::buildStateJson() const {
    json cameras = json::array();
    for (const auto& [id, cfg] : configs_) {
        json caps = json::array();
        auto capIt = capabilities_.find(cfg.devicePath);
        if (capIt != capabilities_.end()) {
            for (const auto& mode : capIt->second) {
                caps.push_back({
                    {"format", mode.format},
                    {"width",  mode.width},
                    {"height", mode.height},
                    {"maxFps", mode.maxFps},
                });
            }
        }
        cameras.push_back({
            {"id",           id},
            {"name",         cfg.name.empty() ? id : cfg.name},
            {"devicePath",   cfg.devicePath},
            {"format",       cfg.format},
            {"enabled",      pipelines_.count(id) > 0},
            {"width",        cfg.width},
            {"height",       cfg.height},
            {"fps",          cfg.fps},
            {"bitrate",      cfg.bitrate},
            {"exposure",     cfg.exposure},
            {"capabilities", caps},
        });
    }
    return json{{"type", "state"}, {"cameras", cameras}}.dump();
}

PipelineStats CameraManager::getCameraStats(const std::string& id) {
    auto it = pipelines_.find(id);
    if (it != pipelines_.end()) return it->second->getStats();
    return {};
}

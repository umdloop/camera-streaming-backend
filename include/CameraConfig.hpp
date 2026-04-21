#pragma once

#include <string>

struct CameraConfig {
    std::string devicePath;
    std::string name;
    std::string format;
    int width    = 1280;
    int height   = 720;
    int fps      = 30;
    int bitrate  = 2000000;
    int exposure = -1;     // -1 = auto; >= 0 = absolute exposure value (v4l2 only)
};

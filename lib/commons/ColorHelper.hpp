#ifndef ATHENA_COLORHELPER_H
#define ATHENA_COLORHELPER_H

#include "imgui.h"

namespace commons {
/**************************************************************************************
 * ColorHelper contains methods to modify Color objects, e.g. adjust color brightness
 **************************************************************************************/
    class ColorHelper {
    public:
        ColorHelper() = delete; // static class
        static ImVec4 adjustBrightness(const ImVec4 &color, float percentage);
    };
} // commons

#endif //ATHENA_COLORHELPER_H

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
        static ImVec4 adjustBrightness(const ImVec4 &color, float factor);
        static ImVec4 withOpacity(const ImVec4 &color, float opacity);

        static bool isEqual(const ImVec4 &color1, const ImVec4 &color2);
    };
} // commons

#endif //ATHENA_COLORHELPER_H

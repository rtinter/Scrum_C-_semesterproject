#ifndef ATHENA_COLORHELPER_H
#define ATHENA_COLORHELPER_H

#include "imgui.h"

namespace commons {
/**
 * @brief provides methods to compare and to modify color objects,
 * e.g. adjust color brightness
 */
    class ColorHelper {
    public:
        ColorHelper() = delete; // static class
        static ImVec4 adjustBrightness(ImVec4 const &color, float const &factor);

        static ImVec4 withOpacity(ImVec4 const &color, float const &opacity);

        static bool isEqual(ImVec4 const &color1, ImVec4 const &color2);
    };
} // commons

#endif //ATHENA_COLORHELPER_H

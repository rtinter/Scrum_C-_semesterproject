#include <algorithm>
#include "ColorHelper.hpp"

namespace commons {
    ImVec4 ColorHelper::adjustBrightness(ImVec4 const &color, float percentage) {
        ImVec4 adjusted = color;
        if (percentage > 1.0f) { // make brighter
            adjusted.x += (1.0f - color.x) * (percentage - 1.0f);
            adjusted.y += (1.0f - color.y) * (percentage - 1.0f);
            adjusted.z += (1.0f - color.z) * (percentage - 1.0f);
        } else { // make darker
            adjusted.x *= percentage;
            adjusted.y *= percentage;
            adjusted.z *= percentage;
        }
        // Values have to be within 0-1
        adjusted.x = std::max(0.0f, std::min(1.0f, adjusted.x));
        adjusted.y = std::max(0.0f, std::min(1.0f, adjusted.y));
        adjusted.z = std::max(0.0f, std::min(1.0f, adjusted.z));
        return adjusted;
    }
} // commons
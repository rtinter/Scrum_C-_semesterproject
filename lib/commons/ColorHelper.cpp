#include <algorithm>
#include "ColorHelper.hpp"

namespace commons {
    /********************************************************************************
     * adjustBrightness() returns a darker or brighter shade of a given ImVec4 color
     * @param color ImVec4 color that should be made brighter or darker
     * @param factor Should be > 1.0 to make color brighter
     * and between 0.0 and 1.0 to make color darker
     * @return Modified ImVec4 color
     ********************************************************************************/
    ImVec4 ColorHelper::adjustBrightness(ImVec4 const &color, float factor) {
        ImVec4 adjusted = color;
        if (factor > 1.0f) { // make color brighter
            adjusted.x += (1.0f - color.x) * (factor - 1.0f); // red
            adjusted.y += (1.0f - color.y) * (factor - 1.0f); // green
            adjusted.z += (1.0f - color.z) * (factor - 1.0f); // blue
        } else { // make color darker
            adjusted.x *= factor; // red
            adjusted.y *= factor; // green
            adjusted.z *= factor; // blue
        }
        // RGB values have to be within 0-1
        adjusted.x = std::max(0.0f, std::min(1.0f, adjusted.x)); // red
        adjusted.y = std::max(0.0f, std::min(1.0f, adjusted.y)); // green
        adjusted.z = std::max(0.0f, std::min(1.0f, adjusted.z)); // blue
        return adjusted;
    }
} // commons
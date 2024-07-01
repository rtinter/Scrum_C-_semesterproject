#include "ColorHelper.hpp"

#include <algorithm>

namespace commons {
    /**
     * @brief Returns a darker or brighter shade of a given ImVec4 color
     * @param color ImVec4 color that should be made brighter or darker
     * @param factor should be > 1.0f to make color brighter
     * and between 0.0f and 1.0f to make color darker
     * @return modified ImVec4 color
     */
    ImVec4 ColorHelper::adjustBrightness(ImVec4 const &color, float const &factor) {
        ImVec4 adjusted{color};
        if (factor > 1.0f) {
            // make color brighter
            adjusted.x += (1.0f - color.x) * (factor - 1.0f); // red
            adjusted.y += (1.0f - color.y) * (factor - 1.0f); // green
            adjusted.z += (1.0f - color.z) * (factor - 1.0f); // blue
        } else {
            // make color darker
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

    /**
     * @brief Returns a color with the same RGB values as the input color
     * but with an adjusted opacity
     * @param color ImVec4 color that should be modified
     * @param opacity new opacity value, should be between 0.0f (no transparency) and 1.0f (full transparency)
     * @return modified ImVec4 color
     */
    ImVec4 ColorHelper::withOpacity(ImVec4 const &color, float const &opacity) {
        return ImVec4(color.x, // red
                      color.y, // green
                      color.z, // blue
                      opacity);
    }

    /**
     * @brief: compares whether two ImVec4 colors are the same
     * @param color1 an ImVec4 color
     * @param color2 another ImVec4 color
     * @return boolean value: Are color1 and color2 the same color?
     */
    bool ColorHelper::isEqual(ImVec4 const &color1, ImVec4 const &color2) {
        static constexpr float EPSILON{0.005f}; // max. difference that is allowed for "same" colors
        return std::abs(color1.x - color2.x) < EPSILON &&
               std::abs(color1.y - color2.y) < EPSILON &&
               std::abs(color1.z - color2.z) < EPSILON &&
               std::abs(color1.w - color2.w) < EPSILON;
    }
} // commons

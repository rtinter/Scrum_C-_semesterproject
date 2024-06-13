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

    /**********************************************************************
     * isEqual() compares whether two ImVec4 colors are the same
     * @param color1 ImVec4
     * @param color2 ImVec4
     * @return boolean value: Are color1 and color2 the same color?
     **********************************************************************/
    bool ColorHelper::isEqual(ImVec4 const &color1, ImVec4 const &color2) {
        float epsilon = 0.005f; // max. difference that is allowed for "same" colors
        return std::abs(color1.x - color2.x) < epsilon &&
               std::abs(color1.y - color2.y) < epsilon &&
               std::abs(color1.z - color2.z) < epsilon &&
               std::abs(color1.w - color2.w) < epsilon;
    }
    
} // commons

#include <map>
#include "imgui.h"

namespace commons {

    /**
     * @brief Loads font and color styles
     * and sets some more style settings, e. g. window rounding.
     * These settings are applied to the entire project.
     */
    class StyleManager {
    public:
        StyleManager() = delete; // static class

        static void loadStyle();
    };

} // commons


#pragma once

namespace commons {
    /**
     * @brief Static class that loads font and color styles
     * and sets some more style settings, e.g. window rounding.
     * These settings are applied to the entire project.
     */
    class StyleManager {
    public:
        StyleManager() = delete;

        static void loadStyle();
    };
} // commons

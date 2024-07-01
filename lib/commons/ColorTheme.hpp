#pragma once

#include <imgui.h>

namespace commons {
    /**
     * @brief Static class that specifies the colors to be used for certain functionalities,
     * e.g. text color, background color, ...
     */
    class ColorTheme {
    public:
        ColorTheme() = delete;

        static ImVec4 const PRIMARY_COLOR;
        static ImVec4 const SECONDARY_COLOR;
        static ImVec4 const BACKGROUND_COLOR;
        static ImVec4 const TEXT_COLOR;
        static ImVec4 const WARNING_COLOR;
        static ImVec4 const SUCCESS_COLOR;
        static ImVec4 const ERROR_COLOR;
        static ImVec4 const ACCENT_COLOR;

        static void setup();
    };
} // commons

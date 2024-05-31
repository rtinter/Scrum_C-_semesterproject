#ifndef ATHENA_COLORTHEME_H
#define ATHENA_COLORTHEME_H

#include "imgui.h"
#include "Colors.hpp"

namespace commons {
/*******************************************************************************
 * ColorTheme defines which colors should be used for certain functionalities,
 * e. g. text color, background color, ...
 ******************************************************************************/
    class ColorTheme {
    public:
        ColorTheme() = delete; // static class
        static ImVec4 const PRIMARY_COLOR;
        static ImVec4 const SECONDARY_COLOR;
        static ImVec4 const BACKGROUND_COLOR;
        static ImVec4 const TEXT_COLOR;
        static ImVec4 const WARNING_COLOR;
        static ImVec4 const SUCCESS_COLOR;
        __attribute__((unused)) static ImVec4 const ACCENT_COLOR;
        static ImVec4 const INFO_COLOR;
        static ImVec4 const ERROR_COLOR;

        /*********************************************************
         * setup() assigns the chosen colors to ImGuiStyle,
         * e. g. ImGuiCol_WindowBg, ImGuiCol_ButtonHovered,....
         *********************************************************/
        static void setup();
    };

} // commons

#endif //ATHENA_COLORTHEME_H

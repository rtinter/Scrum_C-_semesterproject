#ifndef ATHENA_COLORTHEME_H
#define ATHENA_COLORTHEME_H

#include "imgui.h"
#include "Colors.hpp"

namespace commons {
/**
 * @brief Defines which colors should be used for certain functionalities,
 * e. g. text color, background color, ...
 */
    class ColorTheme {
    public:
        ColorTheme() = delete; // static class
        static ImVec4 const PRIMARY_COLOR;
        static ImVec4 const SECONDARY_COLOR;
        static ImVec4 const BACKGROUND_COLOR;
        static ImVec4 const TEXT_COLOR;
        static ImVec4 const WARNING_COLOR;
        static ImVec4 const SUCCESS_COLOR;
        static ImVec4 const ERROR_COLOR;

        static void setup();
    };

} // commons

#endif //ATHENA_COLORTHEME_H

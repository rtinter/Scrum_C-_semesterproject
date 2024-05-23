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
        static ImVec4 const kPRIMARY_COLOR;
        static ImVec4 const kSECONDARY_COLOR;
        static ImVec4 const kBACKGROUND_COLOR;
        static ImVec4 const kTEXT_COLOR;
        static ImVec4 const kWARNING_COLOR;
        static ImVec4 const kSUCCESS_COLOR;
        static ImVec4 const kACCENT_COLOR;
        static ImVec4 const kINFO_COLOR;
        static ImVec4 const kERROR_COLOR;

        /*********************************************************
         * setup() assigns the chosen colors to ImGuiStyle,
         * e. g. ImGuiCol_WindowBg, ImGuiCol_ButtonHovered,....
         *********************************************************/
        static void setup();
    };

} // commons

#endif //ATHENA_COLORTHEME_H

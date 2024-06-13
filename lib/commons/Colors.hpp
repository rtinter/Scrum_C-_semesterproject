#ifndef ATHENA_COLORS_H
#define ATHENA_COLORS_H

#include "imgui.h"

namespace commons {
/***********************************************
 * Colors provides colors as ImVec4 objects.
 * These colors are used by ColorTheme
 * (but can be accessed directly, too).
 **********************************************/
    class Colors {
    public:
        Colors() = delete; // static class

        static ImVec4 const NONE;
        static ImVec4 const LIGHT_GRAY;
        static ImVec4 const DARK_GRAY;
        static ImVec4 const ORANGE;
        static ImVec4 const BLUE;
        static ImVec4 const RED;
        static ImVec4 const GREEN;
        static ImVec4 const INDIGO;
        static ImVec4 const SEAFOAM;
        static ImVec4 const YELLOW;
        static ImVec4 const BROWN;
        static ImVec4 const PURPLE;
        static const ImVec4 BRIGHT_GREEN;
        static const ImVec4 BRIGHT_RED;
        static const ImVec4 VERY_LIGHT_GRAY;
    };
}
// commons

#endif //ATHENA_COLORS_H

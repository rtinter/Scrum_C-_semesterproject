#pragma once

#include <imgui.h>

namespace commons {
    /***********************************************
     * Colors provides colors as ImVec4 objects.
     * These colors are used by ColorTheme
     * (but can be accessed directly, too).
     **********************************************/
    class Colors {
    public:
        Colors() = delete; // static class

        static ImVec4 const TRANSPARENT;
        static const ImVec4 BLACK;
        static ImVec4 const WHITE;
        static ImVec4 const RAISIN_BLACK;
        static ImVec4 const LIGHT_GRAY;
        static ImVec4 const ORANGE;
        static ImVec4 const BLUE;
        static ImVec4 const RED;
        static ImVec4 const GREEN;
        static ImVec4 const INDIGO;
        static ImVec4 const SEAFOAM;
        static ImVec4 const YELLOW;
        static ImVec4 const RICH_YELLOW;
        static ImVec4 const BROWN;
        static ImVec4 const PURPLE;
        static ImVec4 const CORNFLOWER_BLUE;
        static ImVec4 const LIGHT_CORNFLOWER_BLUE;
        static const ImVec4 BRIGHT_GREEN;
        static const ImVec4 BRIGHT_GREEN1;
        static const ImVec4 BRIGHT_GREEN2;
        static const ImVec4 BRIGHT_GREEN3;
        static const ImVec4 BRIGHT_RED;
        static const ImVec4 VERY_LIGHT_GRAY;
        static const ImVec4 LAUREL_GREEN;
        static const ImVec4 GOLD;
        static const ImVec4 EARTH_YELLOW;
    };
}

// commons

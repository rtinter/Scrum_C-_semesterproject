#pragma once

#include <imgui.h>

namespace commons {
    /**
     * @brief Static class that provides colors as ImVec4 objects({red, green, blue, alpha transparency}).
     * These colors are used by ColorTheme (but can be accessed directly, too).
     */
    class Colors {
    public:
        Colors() = delete;

        static ImVec4 const TRANSPARENT;
        static ImVec4 const BLACK;
        static ImVec4 const WHITE;
        static ImVec4 const RAISIN_BLACK;
        static ImVec4 const LIGHT_GRAY;
        static ImVec4 const ORANGE;
        static ImVec4 const BLUE;
        static ImVec4 const CORNFLOWER_BLUE;
        static ImVec4 const RED;
        static ImVec4 const GREEN;
        static ImVec4 const SEAFOAM;
        static ImVec4 const YELLOW;
        static ImVec4 const RICH_YELLOW;
        static ImVec4 const PURPLE;
        static ImVec4 const BRIGHT_GREEN;
        static ImVec4 const BRIGHT_GREEN1;
        static ImVec4 const BRIGHT_GREEN2;
        static ImVec4 const BRIGHT_GREEN3;
        static ImVec4 const BRIGHT_RED;
        static ImVec4 const VERY_LIGHT_GRAY;
        static ImVec4 const LAUREL_GREEN;
        static ImVec4 const GOLD;
        static ImVec4 const EARTH_YELLOW;
    };
}

// commons

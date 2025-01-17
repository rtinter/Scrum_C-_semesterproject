#pragma once

#include <imgui.h>

namespace commons {
    /**
     * @brief Static class that provides different fonts and icons.
     */
    class Fonts {
    public:
        Fonts() = delete;

        [[maybe_unused]] static ImFont *_body; // font for normal text

        static ImFont *_header1; // font for main title
        static ImFont *_header2; // font for 'normal' titles
        static ImFont *_header3; // font for subtitles

        static ImFont *_iconRegular; // font for regular icons
        [[maybe_unused]] static ImFont *_iconSolid; // font for solid icons

        static ImFont *_matrixFontBig; // font for 'code' (Matrix Game)
        static ImFont *_matrixFontSmall; // font for 'code' (Matrix Game)

        static void setup();
    };
} // commons

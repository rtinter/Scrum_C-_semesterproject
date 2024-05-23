#ifndef ATHENA_FONTS_H
#define ATHENA_FONTS_H

#include "imgui.h"

namespace commons {

    /**********************************************************
     * Fonts provides different fonts for titles and text body
     **********************************************************/
    class Fonts {
    public:
        Fonts() = delete; // static class
        static ImFont *_header1; // font for main title
        static ImFont *_header2; // font for 'normal' titles
        static ImFont *_header3; // font for subtitles
        static ImFont *_body; // font for normal text

        /*******************************************************************
         * setup() loads fonts from .ttf files and assigns them to ImGuiIO
         *******************************************************************/
        static void setup();


    };

} // commons

#endif //ATHENA_FONTS_H
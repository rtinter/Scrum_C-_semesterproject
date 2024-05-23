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

        static ImVec4 const kNONE;
        static ImVec4 const kLIGHT_GRAY;
        static ImVec4 const kDARK_GRAY;
        static ImVec4 const kORANGE;
        static ImVec4 const kBLUE;
        static ImVec4 const kRED;
        static ImVec4 const kGREEN;
        static ImVec4 const kINDIGO;
        static ImVec4 const kSEAFOAM;
    };


} // commons

#endif //ATHENA_COLORS_H

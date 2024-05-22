#ifndef ATHENA_COLOR_H
#define ATHENA_COLOR_H

#include "imgui.h"

class Color {
public:
    static ImVec4 constexpr kNONE{0,0,0, 0}; // transparent
    static ImVec4 constexpr kLIGHT_GRAY{0.92, 0.92, 0.92, 1};
    static ImVec4 constexpr kDARK_GRAY{0.22, 0.22, 0.22, 1};
    static ImVec4 constexpr kORANGE{0.9, 0.53, 0.1, 1};
    static ImVec4 constexpr kBLUE{0.08, 0.45, 0.9, 1};
    static ImVec4 constexpr kRED{0.79, 0.15, 0.18, 1};
    static ImVec4 constexpr kGREEN{0.f, 0.63f, 0.f, 1.f};
    static ImVec4 constexpr kINDIGO{0.27, 0.27, 0.78, 1};
    static ImVec4 constexpr kSEAFOAM{0.15, 0.65, 0.67, 1};
};

#endif //ATHENA_COLOR_H

//
// Created by zepi on 16.05.24.
//

#ifndef ATHENA_STYLEMANAGER_HPP
#define ATHENA_STYLEMANAGER_HPP

#include <map>
#include "imgui.h"
#include "Font.h"
#include "Color.h"

namespace commons {

    class StyleManager {



    public: // has to be public, because static (TODO: better solution?)
        StyleManager()=delete; // static class
        static void setupColors();
        static ImVec4 adjustBrightness(ImVec4 const &color, float percentage);
        static void loadStyle();
    };

} // commons

#endif //ATHENA_STYLEMANAGER_HPP

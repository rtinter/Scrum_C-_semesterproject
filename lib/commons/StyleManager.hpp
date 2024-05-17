//
// Created by zepi on 16.05.24.
//

#ifndef ATHENA_STYLEMANAGER_HPP
#define ATHENA_STYLEMANAGER_HPP

#include <map>
#include "imgui.h"
#include "Font.h"

namespace commons {

    class StyleManager {
        StyleManager()=delete;


    public:
        static std::map<Font, ImFont*> fontMap;
        static void setupFonts();
        static void loadStyle();
        static ImFont * getFont(Font const font);
    };

} // commons

#endif //ATHENA_STYLEMANAGER_HPP

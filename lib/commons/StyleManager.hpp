#ifndef ATHENA_STYLEMANAGER_HPP
#define ATHENA_STYLEMANAGER_HPP

#include <map>
#include "imgui.h"

namespace commons {

    /*************************************************************
     * StyleManager::loadStyle() loads font and color styles
     * and sets some more style settings, e. g. window rounding.
     * These settings are applied to the entire project.
     *************************************************************/
    class StyleManager {
    public:
        StyleManager() = delete; // static class

        static void loadStyle();
    };

} // commons

#endif //ATHENA_STYLEMANAGER_HPP

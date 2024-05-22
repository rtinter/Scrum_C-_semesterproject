#ifndef ATHENA_STYLEMANAGER_HPP
#define ATHENA_STYLEMANAGER_HPP

#include <map>
#include "imgui.h"

namespace commons {

    class StyleManager {
    public:
        StyleManager() = delete; // static class
        static void loadStyle();
    };

} // commons

#endif //ATHENA_STYLEMANAGER_HPP

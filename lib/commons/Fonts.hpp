#ifndef ATHENA_FONTS_H
#define ATHENA_FONTS_H

#include "imgui.h"

namespace commons {

    class Fonts {
    public:
        Fonts() = delete;
        static ImFont* _header1;
        static ImFont* _header2;
        static ImFont* _header3;
        static ImFont* _body;
        static void setup();


    };

} // commons

#endif //ATHENA_FONTS_H

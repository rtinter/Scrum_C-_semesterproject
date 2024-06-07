#include "Results.h"
#include "Window.hpp"

namespace views {

    void Results::render() {
        ui_elements::Window("Results").render([this](){
            //Alles, was gerendert werden soll!
        });
    }
} // views
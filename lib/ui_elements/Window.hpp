#pragma once

#include "imgui.h"
#include <string>
#include <vector>

namespace ui_elements {

    /*************************************************************************************
     * The wrapper class "Window" offers a more convenient and cleaner way of creating
     * new ImGui windows. The default flags for this project are set automatically.
     **************************************************************************************/
    class Window {
    public:
        explicit Window(std::string name, bool *p_open = nullptr,
                        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
                                                 ImGuiWindowFlags_NoDecoration);

        bool begin();

        static void end();

        template<typename Functor>
        void render(Functor &&functor) {
            if (begin()) {
                functor();
                end();
            }
        }

    private:
        std::string _name;
        bool *_pOpen{nullptr};
        ImGuiWindowFlags _flags{};
    };

}

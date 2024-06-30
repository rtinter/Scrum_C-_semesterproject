#pragma once

#include "imgui.h"
#include <string>

namespace ui_elements {

    /*************************************************************************************
     * The wrapper class "Window" offers a more convenient and cleaner way of creating
     * new ImGui windows. The default flags for this project are set automatically.
     **************************************************************************************/
    class Window {
        std::string _name;
        bool *_pOpen{nullptr};
        ImGuiWindowFlags _flags{};
    public:
        explicit Window(std::string const &name, bool *p_open = nullptr,
                        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
                                                 ImGuiWindowFlags_NoTitleBar |
                                                 ImGuiWindowFlags_NoDecoration |
                                                 ImGuiWindowFlags_NoBringToFrontOnFocus |
                                                 ImGuiWindowFlags_NoMove
        );

        bool begin();

        static void end();

        template<typename Functor>
        void render(Functor &&functor) {
            if (begin()) {
                functor();
                end();
            }
        }

    };

}

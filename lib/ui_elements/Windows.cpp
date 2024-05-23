#include "Window.hpp"
#include "imgui.h"

namespace ui_elements {

    bool Window::begin() {
        _visible = ImGui::Begin(_name, _pOpen, _flags);
        return _visible;
    }

    void Window::end() {
        ImGui::End();
    }
}
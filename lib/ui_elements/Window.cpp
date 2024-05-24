#include "Window.hpp"

#include "imgui.h"

namespace ui_elements {

    // Constructor definition
    Window::Window(std::string name, bool *p_open, ImGuiWindowFlags flags)
        : _name(std::move(name)), _pOpen(p_open), _flags(flags) {}

    bool Window::begin() {
        if (_name.empty()) {
            return false;
        }
        return ImGui::Begin(_name.c_str(), _pOpen, _flags);
    }

    void Window::end() {
        ImGui::End();
    }

}

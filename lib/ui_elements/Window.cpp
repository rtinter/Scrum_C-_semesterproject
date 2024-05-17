#include "Window.hpp"

#include "imgui.h"

namespace ui_elements {

    Window::~Window() {
        if (_visible) {
            end();
        }
    }

    bool Window::begin() {
        _visible = ImGui::Begin(_name, _pOpen, _flags);
        return _visible;
    }

    void Window::end() {
        ImGui::End();
    }

    template<typename Functor>
    void Window::render(Functor &&functor) {
        if (begin()) {
            functor();
            end();
        }
    }
}

#include "Overlay.hpp"
#include <imgui.h>

namespace ui_elements {
    Overlay::Overlay(const char *name, bool &showModal) : _name(name), _showModal(showModal) {
    }

    void Overlay::begin() {
        if (_showModal) {

            ImGui::SetNextWindowSize(ImVec2(1000, 600));

            ImGui::OpenPopup(_name);

            _showModal = false;
        }
        ImGui::BeginPopupModal(_name, nullptr,
                               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                               ImGuiWindowFlags_NoDecoration);

    }

    void Overlay::end() {

        ImGui::EndPopup();
    }
}

// ui_elements

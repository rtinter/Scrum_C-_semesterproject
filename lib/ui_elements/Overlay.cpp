#include "Overlay.hpp"
#include <imgui.h>

namespace ui_elements {
    Overlay::Overlay(char const *name, bool &showModal) : _name(name), _showModal(showModal) {
    }

    void Overlay::render(std::function<void()> const &callback) const {
        if (_showModal) {
            ImGui::OpenPopup(_name);

            static constexpr float const WINDOW_HEIGHT {600};
            static constexpr float const WINDOW_WIDTH {1000};

            ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT), ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x / 2) - (WINDOW_WIDTH / 2),
                                           (ImGui::GetIO().DisplaySize.y / 2) - (WINDOW_HEIGHT / 2)), ImGuiCond_Always);

            if (ImGui::BeginPopupModal(_name, nullptr,
                                       ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar
                                       |
                                       ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize)) {
                callback();
                ImGui::EndPopup();
            }
        }
    }
}

// ui_elements

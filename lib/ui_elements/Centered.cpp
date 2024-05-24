//
// Created by zepi on 24.05.24.
//

#include <Centered.hpp>

#include <imgui.h>

namespace ui_elements {
    Centered::Centered(const std::function<void()>& callback) {
        ImGui::BeginGroup();

        ImVec2 windowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPosX((windowSize.x - ImGui::CalcItemWidth()/2) * 0.5f);

        ImGui::BeginGroup();
        callback();
        ImGui::EndGroup();
        ImGui::EndGroup();
    }

} // ui_elements

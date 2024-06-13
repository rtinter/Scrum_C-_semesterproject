#include <Centered.hpp>

#include <imgui.h>

namespace ui_elements {
    Centered::Centered(const std::function<void()> &content) {
        float availableWidth = ImGui::GetContentRegionAvail().x;
        float initialCursorPosX = ImGui::GetCursorPos().x;

        ImGui::Dummy(ImVec2(0, 0));
        float leftDummyCursorPosX = ImGui::GetCursorPos().x;

        ImGui::PushClipRect(ImVec2(0, 0), ImVec2(0, 0), true);
        content();
        ImGui::PopClipRect();
        float contentCursorPosX = ImGui::GetCursorPos().x;
        float contentWidth = contentCursorPosX - leftDummyCursorPosX;

        float padding = (availableWidth - contentWidth) / 2.0f;


        ImGui::SetCursorPosX(initialCursorPosX);
        ImGui::Dummy(ImVec2(padding, 200));
        ImGui::SameLine();

        content();
        ImGui::SameLine();

        ImGui::Dummy(ImVec2(padding, 200));

    }

} // ui_elements

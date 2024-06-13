#include "Centered.hpp"

#include <imgui.h>


namespace ui_elements {
    Centered::Centered(bool horizontal, bool vertical, const std::function<void()> &content) {
        ImVec2 available = ImGui::GetContentRegionAvail();
        ImVec2 inital = ImGui::GetCursorPos();

        ImGui::PushClipRect(ImVec2(0, 0), ImVec2(0, 0), true);
        ImGui::BeginGroup();
        content();
        ImGui::EndGroup();
        ImVec2 contentSize = ImGui::GetItemRectSize();
        ImGui::PopClipRect();


        ImGui::SetCursorPos(inital);
        ImGui::Dummy(contentSize);


        float hPAdding = (available.x - contentSize.x) / 2.0f;
        float vPAdding = (available.y - contentSize.y) / 2.0f;


        if (horizontal) {
            ImGui::SetCursorPosX(inital.x + hPAdding);
        }
        if (vertical) {
            ImGui::SetCursorPosY(inital.y + vPAdding);
        }
        ImGui::BeginChild("##Child", contentSize);
        content();
        ImGui::EndChild();
    }
} // ui_elements

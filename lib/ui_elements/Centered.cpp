#include "Centered.hpp"

#include <imgui.h>


namespace ui_elements {
    Centered::Centered(bool horizontal, bool vertical, std::function<void()> const &content) {
        float availableX {ImGui::GetContentRegionAvail().x};
        float availableY {ImGui::GetContentRegionAvail().y};
        ImVec2 inital{ImGui::GetCursorPos()};

        ImGui::PushClipRect(ImVec2(0, 0), ImVec2(0, 0), true);
        ImGui::BeginGroup();
        content();
        ImGui::EndGroup();
        ImVec2 contentSize{ImGui::GetItemRectSize()};
        ImGui::PopClipRect();


        float hPAdding{(availableX - contentSize.x) / 2.0f};
        float vPAdding{(availableY - contentSize.y) / 2.0f};


        ImGui::SetCursorPos(inital);
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

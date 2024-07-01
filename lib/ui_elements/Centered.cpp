#include "Centered.hpp"

#include <imgui.h>


namespace ui_elements {
    Centered::Centered(bool const horizontal, bool const vertical, std::function<void()> const &callback) {
        float const availableX {ImGui::GetContentRegionAvail().x};
        float const availableY {ImGui::GetContentRegionAvail().y};
        ImVec2 const inital{ImGui::GetCursorPos()};

        ImGui::PushClipRect(ImVec2(0, 0), ImVec2(0, 0), true);
        ImGui::BeginGroup();
        callback();
        ImGui::EndGroup();
        ImVec2 const contentSize{ImGui::GetItemRectSize()};
        ImGui::PopClipRect();


        float const hPAdding{(availableX - contentSize.x) / 2.0f};
        float const vPAdding{(availableY - contentSize.y) / 2.0f};


        ImGui::SetCursorPos(inital);
        if (horizontal) {
            ImGui::SetCursorPosX(inital.x + hPAdding);
        }
        if (vertical) {
            ImGui::SetCursorPosY(inital.y + vPAdding);
        }
        ImGui::BeginChild("##Child", contentSize);
        callback();
        ImGui::EndChild();
    }
} // ui_elements

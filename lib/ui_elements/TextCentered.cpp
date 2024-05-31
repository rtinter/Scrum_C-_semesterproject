//
// Created by zepi on 24.05.24.
//

#include "TextCentered.hpp"
#include <imgui.h>

namespace ui_elements {

    TextCentered::TextCentered(const char* content) {
        ImVec2 textSize = ImGui::CalcTextSize(content);

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textSize.x) / 2.0f);
        ImGui::Text("%s", content);
    }
} // ui_elements

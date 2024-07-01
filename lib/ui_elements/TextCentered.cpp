#include "TextCentered.hpp"
#include <imgui.h>

namespace ui_elements {

    TextCentered::TextCentered(char const *content) {
        float textSizeX {ImGui::CalcTextSize(content).x};

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - textSizeX) / 2.0f);
        ImGui::Text("%s", content);
    }
} // ui_elements

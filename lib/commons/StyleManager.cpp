#include "imgui.h"
#include "StyleManager.hpp"
#include "ColorTheme.hpp"
#include "Fonts.hpp"

namespace commons {
    void StyleManager::loadStyle() {
        Fonts::setup();
        ColorTheme::setup();

        // Some more style settings
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 7.f; // rounded corners
        style.FrameRounding = 7.f; // applies for buttons too
        style.ItemSpacing = ImVec2(16.f, 16.f); // space between items: 16 pixels
        style.FramePadding = ImVec2(7.f, 7.f); // space between frame content (e.g. text) and frame border
    }
} // commons

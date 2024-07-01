#include "StyleManager.hpp"

#include <imgui.h>

#include "ColorTheme.hpp"
#include "Fonts.hpp"

namespace commons {
    void StyleManager::loadStyle() {
        // Set up fonts and color theme
        Fonts::setup();
        ColorTheme::setup();

        // Some more style settings
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 7.f; // rounded corners
        style.FrameRounding = 7.f; // applies for buttons too
        style.ItemSpacing = ImVec2(16.f, 16.f); // space between items: 16 pixels
        style.FramePadding = ImVec2(10.f, 10.f); // space between frame content (e.g. text) and frame border
    }
} // commons

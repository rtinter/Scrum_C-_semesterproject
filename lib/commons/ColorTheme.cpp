#include "ColorTheme.hpp"
#include "ColorHelper.hpp"

namespace commons {
    ImVec4 const ColorTheme::BACKGROUND_COLOR = Colors::WHITE;
    ImVec4 const ColorTheme::TEXT_COLOR = Colors::RAISIN_BLACK;
    ImVec4 const ColorTheme::PRIMARY_COLOR = Colors::LAUREL_GREEN;
    ImVec4 const ColorTheme::SECONDARY_COLOR = Colors::GOLD;
    ImVec4 const ColorTheme::WARNING_COLOR = Colors::ORANGE;
    ImVec4 const ColorTheme::SUCCESS_COLOR = Colors::BRIGHT_GREEN;
    ImVec4 const ColorTheme::ACCENT_COLOR = Colors::EARTH_YELLOW;
    ImVec4 const ColorTheme::ERROR_COLOR = Colors::BRIGHT_RED;

    /**
    * @brief assigns chosen colors to respective ImGuiStyle,
    * e. g. ImGuiCol_WindowBg, ImGuiCol_ButtonHovered,....
    */
    void ColorTheme::setup() {
        ImGuiStyle &style{ImGui::GetStyle()};

        // Text Colors
        style.Colors[ImGuiCol_Text] = TEXT_COLOR;
        style.Colors[ImGuiCol_TextDisabled] = ColorHelper::withOpacity(TEXT_COLOR, 0.8);
        style.Colors[ImGuiCol_TextSelectedBg] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.75f);

        // Button Colors
        style.Colors[ImGuiCol_Button] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_ButtonHovered] = ColorHelper::adjustBrightness(ImGui::GetStyle().Colors[ImGuiCol_Button],
                                                                             1.2);
        style.Colors[ImGuiCol_ButtonActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.4f);

        // Border Colors
        style.Colors[ImGuiCol_Border] = Colors::TRANSPARENT;
        style.Colors[ImGuiCol_BorderShadow] = Colors::RAISIN_BLACK;

        // Background Colors
        style.Colors[ImGuiCol_WindowBg] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_ChildBg] = Colors::TRANSPARENT;
        style.Colors[ImGuiCol_PopupBg] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 1.3f);
        style.Colors[ImGuiCol_FrameBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_FrameBgActive] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_TitleBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_TitleBgActive] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_MenuBarBg] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_ScrollbarBg] = BACKGROUND_COLOR;

        // Other
        style.Colors[ImGuiCol_ScrollbarGrab] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.65f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.5f);
        style.Colors[ImGuiCol_CheckMark] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.9f);
        style.Colors[ImGuiCol_SliderGrab] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_SliderGrabActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.65f);
        style.Colors[ImGuiCol_Header] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_HeaderHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_HeaderActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.65f);
        style.Colors[ImGuiCol_Separator] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_SeparatorHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.6f);
        style.Colors[ImGuiCol_SeparatorActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45f);
        style.Colors[ImGuiCol_ResizeGrip] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.75f);
        style.Colors[ImGuiCol_ResizeGripHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.6f);
        style.Colors[ImGuiCol_ResizeGripActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45f);
        style.Colors[ImGuiCol_PlotLines] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotLinesHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_PlotHistogram] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotHistogramHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8f);
        style.Colors[ImGuiCol_DragDropTarget] = WARNING_COLOR;
        style.Colors[ImGuiCol_NavHighlight] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45f);
        style.Colors[ImGuiCol_NavWindowingHighlight] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_NavWindowingDimBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8f);
    }
} // commons

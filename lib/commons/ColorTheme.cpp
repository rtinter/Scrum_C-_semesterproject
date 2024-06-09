#include "ColorTheme.hpp"
#include "ColorHelper.hpp"

namespace commons {
    ImVec4 const ColorTheme::PRIMARY_COLOR = Colors::SEAFOAM;
    ImVec4 const ColorTheme::SECONDARY_COLOR = Colors::LIGHT_GRAY;
    ImVec4 const ColorTheme::BACKGROUND_COLOR = Colors::LIGHT_GRAY;
    ImVec4 const ColorTheme::TEXT_COLOR = Colors::DARK_GRAY;
    ImVec4 const ColorTheme::WARNING_COLOR = Colors::ORANGE;
    ImVec4 const ColorTheme::ACCENT_COLOR = Colors::INDIGO;
    ImVec4 const ColorTheme::INFO_COLOR = Colors::BLUE;
    ImVec4 const ColorTheme::SUCCESS_COLOR = Colors::BRIGHT_GREEN;
    ImVec4 const ColorTheme::ERROR_COLOR = Colors::BRIGHT_RED;

    void ColorTheme::setup() {
        ImGuiStyle &style{ImGui::GetStyle()};

        // Text Colors
        style.Colors[ImGuiCol_Text] = TEXT_COLOR;
        style.Colors[ImGuiCol_TextDisabled] = ColorHelper::adjustBrightness(TEXT_COLOR, 1.1f);
        style.Colors[ImGuiCol_TextSelectedBg] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.75f);

        // Button Colors
        style.Colors[ImGuiCol_Button] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_ButtonHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.9f);
        style.Colors[ImGuiCol_ButtonActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.4f);

        // Border Colors
        style.Colors[ImGuiCol_Border] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 1.1f);
        style.Colors[ImGuiCol_BorderShadow] = Colors::NONE;

        // Background Colors
        style.Colors[ImGuiCol_WindowBg] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_ChildBg] = Colors::NONE;
        style.Colors[ImGuiCol_PopupBg] = ColorHelper::adjustBrightness(INFO_COLOR,
                                                                       1.1f); // applies also to tooltips
        style.Colors[ImGuiCol_FrameBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_FrameBgActive] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_TitleBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_TitleBgActive] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_MenuBarBg] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_ScrollbarBg] = BACKGROUND_COLOR;

        // Other
        style.Colors[ImGuiCol_ScrollbarGrab] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.8);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.65);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.5);
        style.Colors[ImGuiCol_CheckMark] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.9);
        style.Colors[ImGuiCol_SliderGrab] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_SliderGrabActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.65);
        style.Colors[ImGuiCol_Header] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_HeaderHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_HeaderActive] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.65);
        style.Colors[ImGuiCol_Separator] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.8);
        style.Colors[ImGuiCol_SeparatorHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.6);
        style.Colors[ImGuiCol_SeparatorActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_ResizeGrip] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.75);
        style.Colors[ImGuiCol_ResizeGripHovered] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.6);
        style.Colors[ImGuiCol_ResizeGripActive] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_PlotLines] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotLinesHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_PlotHistogram] = PRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotHistogramHovered] = ColorHelper::adjustBrightness(PRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_DragDropTarget] = WARNING_COLOR;
        style.Colors[ImGuiCol_NavHighlight] = ColorHelper::adjustBrightness(SECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_NavWindowingHighlight] = BACKGROUND_COLOR;
        style.Colors[ImGuiCol_NavWindowingDimBg] = ColorHelper::adjustBrightness(BACKGROUND_COLOR, 0.8);
    }
} // commons
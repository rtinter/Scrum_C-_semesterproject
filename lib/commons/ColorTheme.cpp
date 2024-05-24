#include "ColorTheme.hpp"
#include "ColorHelper.hpp"

namespace commons {
    ImVec4 const ColorTheme::kPRIMARY_COLOR = Colors::kSEAFOAM;
    ImVec4 const ColorTheme::kSECONDARY_COLOR = Colors::kLIGHT_GRAY;
    ImVec4 const ColorTheme::kBACKGROUND_COLOR = Colors::kLIGHT_GRAY;
    ImVec4 const ColorTheme::kTEXT_COLOR = Colors::kDARK_GRAY;
    ImVec4 const ColorTheme::kWARNING_COLOR = Colors::kORANGE;
    ImVec4 const ColorTheme::kACCENT_COLOR = Colors::kINDIGO;
    ImVec4 const ColorTheme::kINFO_COLOR = Colors::kBLUE;
    ImVec4 const ColorTheme::kSUCCESS_COLOR = Colors::kGREEN;
    ImVec4 const ColorTheme::kERROR_COLOR = Colors::kRED;

    void ColorTheme::setup() {
        ImGuiStyle &style{ImGui::GetStyle()};

        // Text Colors
        style.Colors[ImGuiCol_Text] = kTEXT_COLOR;
        style.Colors[ImGuiCol_TextDisabled] = ColorHelper::adjustBrightness(kTEXT_COLOR, 1.1f);
        style.Colors[ImGuiCol_TextSelectedBg] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.75f);

        // Button Colors
        style.Colors[ImGuiCol_Button] = kPRIMARY_COLOR;
        style.Colors[ImGuiCol_ButtonHovered] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.9f);
        style.Colors[ImGuiCol_ButtonActive] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.4f);

        // Border Colors
        style.Colors[ImGuiCol_Border] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 1.1f);
        style.Colors[ImGuiCol_BorderShadow] = Colors::kNONE;

        // Background Colors
        style.Colors[ImGuiCol_WindowBg] = kBACKGROUND_COLOR;
        style.Colors[ImGuiCol_ChildBg] = Colors::kNONE;
        style.Colors[ImGuiCol_PopupBg] = ColorHelper::adjustBrightness(kINFO_COLOR,
                                                                       1.1f); // applies also to tooltips
        style.Colors[ImGuiCol_FrameBg] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_FrameBgActive] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_TitleBg] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.8f);
        style.Colors[ImGuiCol_TitleBgActive] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.6f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.4f);
        style.Colors[ImGuiCol_MenuBarBg] = kBACKGROUND_COLOR;
        style.Colors[ImGuiCol_ScrollbarBg] = kBACKGROUND_COLOR;

        // Other
        style.Colors[ImGuiCol_ScrollbarGrab] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.8);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.65);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.5);
        style.Colors[ImGuiCol_CheckMark] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.9);
        style.Colors[ImGuiCol_SliderGrab] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_SliderGrabActive] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.65);
        style.Colors[ImGuiCol_Header] = kPRIMARY_COLOR;
        style.Colors[ImGuiCol_HeaderHovered] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_HeaderActive] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.65);
        style.Colors[ImGuiCol_Separator] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.8);
        style.Colors[ImGuiCol_SeparatorHovered] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.6);
        style.Colors[ImGuiCol_SeparatorActive] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_ResizeGrip] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.75);
        style.Colors[ImGuiCol_ResizeGripHovered] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.6);
        style.Colors[ImGuiCol_ResizeGripActive] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_PlotLines] = kPRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotLinesHovered] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_PlotHistogram] = kPRIMARY_COLOR;
        style.Colors[ImGuiCol_PlotHistogramHovered] = ColorHelper::adjustBrightness(kPRIMARY_COLOR, 0.8);
        style.Colors[ImGuiCol_DragDropTarget] = kWARNING_COLOR;
        style.Colors[ImGuiCol_NavHighlight] = ColorHelper::adjustBrightness(kSECONDARY_COLOR, 0.45);
        style.Colors[ImGuiCol_NavWindowingHighlight] = kBACKGROUND_COLOR;
        style.Colors[ImGuiCol_NavWindowingDimBg] = ColorHelper::adjustBrightness(kBACKGROUND_COLOR, 0.8);
    }
} // commons
#include <iostream>
#include "StyleManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Color.h"
#include "Fonts.h"


namespace commons {
    //--------------------------//
    //          Colors          //
    //--------------------------//
    ImVec4 StyleManager::adjustBrightness( ImVec4 const &color, float percentage) {
        ImVec4 adjusted = color;
        if (percentage > 1.0f) { // make brighter
            adjusted.x += (1.0f - color.x) * (percentage - 1.0f);
            adjusted.y += (1.0f - color.y) * (percentage - 1.0f);
            adjusted.z += (1.0f - color.z) * (percentage - 1.0f);
        } else { // make darker
            adjusted.x *= percentage;
            adjusted.y *= percentage;
            adjusted.z *= percentage;
        }
        // Values have to be within 0-1
        adjusted.x = std::max(0.0f, std::min(1.0f, adjusted.x));
        adjusted.y = std::max(0.0f, std::min(1.0f, adjusted.y));
        adjusted.z = std::max(0.0f, std::min(1.0f, adjusted.z));
        return adjusted;
    }

    void StyleManager::setupColors(){
        //---------------//
        // Define Colors //
        //---------------//

        ImVec4 const primaryColor{Color::kSEAFOAM};
        ImVec4 const secondaryColor{Color::kLIGHT_GRAY};
        ImVec4 const backgroundColor{Color::kLIGHT_GRAY};
        ImVec4 const textColor{Color::kDARK_GRAY};
        ImVec4 const warningColor{Color::kORANGE};
        /*
        // Not used yet:
        ImVec4 const accentColor{Color::kINDIGO};
        ImVec4 const infoColor{Color::kBLUE};
        ImVec4 const successColor{Color::kGREEN};
        ImVec4 const errorColor{Color::kRED};
         */

        //----------------//
        //  Assign Colors //
        //----------------//
        ImGuiStyle &style{ImGui::GetStyle()};

        // Text Colors
        style.Colors[ImGuiCol_Text] = textColor;
        style.Colors[ImGuiCol_TextDisabled] = adjustBrightness(textColor, 1.1f);
        style.Colors[ImGuiCol_TextSelectedBg] = adjustBrightness(primaryColor, 0.75f);

        // Button Colors
        style.Colors[ImGuiCol_Button] = primaryColor;
        style.Colors[ImGuiCol_ButtonHovered] = adjustBrightness(primaryColor, 0.9f);
        style.Colors[ImGuiCol_ButtonActive] = adjustBrightness(primaryColor, 0.4f);

        // Border Colors
        style.Colors[ImGuiCol_Border] = adjustBrightness(backgroundColor, 1.1f);
        style.Colors[ImGuiCol_BorderShadow] = Color::kNONE;

        // Background Colors
        style.Colors[ImGuiCol_WindowBg] = backgroundColor;
        style.Colors[ImGuiCol_ChildBg] = Color::kNONE;
        style.Colors[ImGuiCol_PopupBg] =  adjustBrightness(backgroundColor, 1.1f); // applies also to tooltips
        style.Colors[ImGuiCol_FrameBg] = adjustBrightness(backgroundColor, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered] = adjustBrightness(backgroundColor, 0.6f);
        style.Colors[ImGuiCol_FrameBgActive] = adjustBrightness(backgroundColor, 0.4f);
        style.Colors[ImGuiCol_TitleBg] = adjustBrightness(backgroundColor, 0.8f);
        style.Colors[ImGuiCol_TitleBgActive] =  adjustBrightness(backgroundColor, 0.6f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = adjustBrightness(backgroundColor, 0.4f);
        style.Colors[ImGuiCol_MenuBarBg] = backgroundColor;
        style.Colors[ImGuiCol_ScrollbarBg] = backgroundColor;

        // Other
        style.Colors[ImGuiCol_ScrollbarGrab] = adjustBrightness(secondaryColor, 0.8);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = adjustBrightness(secondaryColor, 0.65);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = adjustBrightness(secondaryColor, 0.5);
        style.Colors[ImGuiCol_CheckMark] = adjustBrightness(primaryColor, 0.9);
        style.Colors[ImGuiCol_SliderGrab] = adjustBrightness(primaryColor, 0.8);
        style.Colors[ImGuiCol_SliderGrabActive] = adjustBrightness(primaryColor, 0.65);
        style.Colors[ImGuiCol_Header] = primaryColor;
        style.Colors[ImGuiCol_HeaderHovered] = adjustBrightness(primaryColor, 0.8);
        style.Colors[ImGuiCol_HeaderActive] = adjustBrightness(primaryColor, 0.65);
        style.Colors[ImGuiCol_Separator] = adjustBrightness(secondaryColor, 0.8);
        style.Colors[ImGuiCol_SeparatorHovered] = adjustBrightness(secondaryColor, 0.6);
        style.Colors[ImGuiCol_SeparatorActive] = adjustBrightness(secondaryColor, 0.45);
        style.Colors[ImGuiCol_ResizeGrip] = adjustBrightness(secondaryColor, 0.75);
        style.Colors[ImGuiCol_ResizeGripHovered] = adjustBrightness(secondaryColor, 0.6);
        style.Colors[ImGuiCol_ResizeGripActive] = adjustBrightness(secondaryColor, 0.45);
        style.Colors[ImGuiCol_PlotLines] = primaryColor;
        style.Colors[ImGuiCol_PlotLinesHovered] = adjustBrightness(primaryColor, 0.8);
        style.Colors[ImGuiCol_PlotHistogram] = primaryColor;
        style.Colors[ImGuiCol_PlotHistogramHovered] = adjustBrightness(primaryColor, 0.8);
        style.Colors[ImGuiCol_DragDropTarget] = warningColor;
        style.Colors[ImGuiCol_NavHighlight] = adjustBrightness(secondaryColor, 0.45);
        style.Colors[ImGuiCol_NavWindowingHighlight] = backgroundColor;
        style.Colors[ImGuiCol_NavWindowingDimBg] = adjustBrightness(backgroundColor, 0.8);
        }


    //-------------------------------//
    //          Load Style           //
    //-------------------------------//
    void StyleManager::loadStyle() {
        Fonts::setup();
        setupColors();

        // Some more style settings
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 7.f; // rounded corners
        style.FrameRounding = 7.f; // applies for buttons too
        style.ItemSpacing = ImVec2(16.f, 16.f); // space between items: 16 pixels
        style.FramePadding = ImVec2(7.f, 7.f); // space between frame content (e.g. text) and frame border
    }
} // commons

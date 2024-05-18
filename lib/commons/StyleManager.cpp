#include <iostream>
#include "StyleManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


namespace commons {

    //--------------------------//
    //          Fonts           //
    //--------------------------//
    std::map<Font, ImFont*> StyleManager::fontMap;

    void StyleManager::setupFonts(){
        ImGuiIO &io{ImGui::GetIO()};
        io.Fonts->Clear();
        // current working directory is athena/cmake-build-debug/bin
        fontMap[Font::BODY] =
                io.Fonts->AddFontFromFileTTF("../../lib/commons/fonts/Roboto-Light.ttf", 25.0);
        fontMap[Font::HEADER1] =
                io.Fonts->AddFontFromFileTTF("../../lib/commons/fonts/Roboto-Bold.ttf", 80.0);
        fontMap[Font::HEADER2] =
                io.Fonts->AddFontFromFileTTF("../../lib/commons/fonts/Roboto-Medium.ttf", 40.0);
        fontMap[Font::HEADER3] =
                io.Fonts->AddFontFromFileTTF("../../lib/commons/fonts/Roboto-Medium.ttf", 30.0);
        io.Fonts->Build();
        ImGui::SFML::UpdateFontTexture();
    }

    ImFont * StyleManager::getFont(Font const font) {
        return fontMap[font];
    }

    //--------------------------//
    //          Colors          //
    //--------------------------//
    ImVec4 StyleManager::adjustBrightness(const ImVec4& color, float percentage) {
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
        ImVec4 const NONE{0,0,0, 0}; // transparent
        ImVec4 const SEAFOAM{0.15, 0.65, 0.67, 1};
        ImVec4 const LIGHT_GRAY{0.92, 0.92, 0.92, 1};
        ImVec4 const DARK_GRAY{0.22, 0.22, 0.22, 1};
        ImVec4 const ORANGE{0.9, 0.53, 0.1, 1};
        ImVec4 const BLUE{0.08, 0.45, 0.9, 1};
        ImVec4 const RED{0.79, 0.15, 0.18, 1};
        ImVec4 const GREEN{0.f, 0.63f, 0.f, 1.f};
        ImVec4 const INDIGO{0.27, 0.27, 0.78, 1};

        // TODO @Jane: Brauchen wir davon alles?
        ImVec4 const primaryColor{SEAFOAM};
        ImVec4 const secondaryColor{LIGHT_GRAY};
        ImVec4 const backgroundColor{LIGHT_GRAY};
        ImVec4 const textColor{DARK_GRAY};
        ImVec4 const accentColor{INDIGO};
        ImVec4 const infoColor{BLUE};
        ImVec4 const successColor{GREEN};
        ImVec4 const warningColor{ORANGE};
        ImVec4 const errorColor{RED};

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
        style.Colors[ImGuiCol_BorderShadow] = NONE;

        // Background Colors
        style.Colors[ImGuiCol_WindowBg] = backgroundColor;
        style.Colors[ImGuiCol_ChildBg] = NONE;
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
        style.Colors[ImGuiCol_DragDropTarget] = ORANGE;
        style.Colors[ImGuiCol_NavHighlight] = adjustBrightness(secondaryColor, 0.45);
        style.Colors[ImGuiCol_NavWindowingHighlight] = backgroundColor;
        style.Colors[ImGuiCol_NavWindowingDimBg] = adjustBrightness(backgroundColor, 0.8);
        }


    //-------------------------------//
    //          Load Style           //
    //-------------------------------//
    void StyleManager::loadStyle() {
        setupFonts();
        setupColors();

        // Some more style settings
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 7.f; // rounded corners
        style.FrameRounding = 7.f; // applies for buttons too
        style.ItemSpacing = ImVec2(16.f, 16.f); // space between items: 16 pixels
        style.FramePadding = ImVec2(7.f, 7.f); // space between frame content (e.g. text) and frame border
    }
} // commons

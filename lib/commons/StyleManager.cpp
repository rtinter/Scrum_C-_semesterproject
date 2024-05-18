#include "StyleManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"


namespace commons {

    std::map<Font, ImFont*> StyleManager::fontMap;
    ImVec4 const NONE{0,0,0, 0}; // transparent
    ImVec4 const WHITE{1, 1, 1, 1};
    ImVec4 const GRAY75{0.98, 0.98, 0.98, 1};
    ImVec4 const GRAY100{0.96, 0.96, 0.96, 1};
    ImVec4 const GRAY200{0.92, 0.92, 0.92, 1};
    ImVec4 const GRAY300{0.88, 0.88, 0.88, 1};
    ImVec4 const GRAY400{0.79, 0.79, 0.79, 1};
    ImVec4 const GRAY500{0.7, 0.7, 0.7, 1};
    ImVec4 const GRAY600{0.56, 0.56, 0.56, 1};
    ImVec4 const GRAY700{0.44, 0.44, 0.44, 1};
    ImVec4 const GRAY800{0.29, 0.29, 0.29, 1};

    ImVec4 const ORANGE{0.9, 0.53, 0.1, 1};
    ImVec4 const BLUE{0.08, 0.45, 0.9, 1};
    ImVec4 const RED{0.79, 0.15, 0.18, 1};
    ImVec4 const GREEN{0.f, 0.63f, 0.f, 1.f};
    ImVec4 const INDIGO{0.27, 0.27, 0.78, 1};
    ImVec4 const SEAFOAM400{0.11, 0.58, 0.6, 1};
    ImVec4 const SEAFOAM500{0.09, 0.53, 0.55, 1};
    ImVec4 const SEAFOAM600{0.06, 0.47, 0.49, 1};
    ImVec4 const SEAFOAM700{0.04, 0.42, 0.44, 1};

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

    void setupColors(){

        // Feel free to adjust and add more!
        ImVec4 primaryColor{0.25f, 0.67f, 0.75f, 1.f};
        ImVec4 secondaryColor{0.27f, 0.6f, 0.65f, 1.f};
        ImVec4 accentColor{0.25f, 0.8f, 0.81f, 1.f};
        ImVec4 backgroundColor{0.93f, 1.f, 0.95f, 1.f};
        ImVec4 textColor{GRAY800};
        ImVec4 infoColor{BLUE};
        ImVec4 successColor{GREEN};
        ImVec4 warningColor{ORANGE};
        ImVec4 errorColor{RED};

        ImGuiStyle &style{ImGui::GetStyle()};
        style.Colors[ImGuiCol_Text] = textColor; // text on hovered controls is gray900
        style.Colors[ImGuiCol_TextDisabled] = GRAY500;
        style.Colors[ImGuiCol_WindowBg] = GRAY100;
        style.Colors[ImGuiCol_ChildBg] = NONE;
        style.Colors[ImGuiCol_PopupBg] =  WHITE; // applies also to tooltips
        style.Colors[ImGuiCol_Border] = GRAY300;
        style.Colors[ImGuiCol_BorderShadow] = NONE;
        style.Colors[ImGuiCol_FrameBg] = GRAY200;
        style.Colors[ImGuiCol_FrameBgHovered] = GRAY100;
        style.Colors[ImGuiCol_FrameBgActive] = GRAY300;
        style.Colors[ImGuiCol_TitleBg] = GRAY300;
        style.Colors[ImGuiCol_TitleBgActive] = GRAY200;
        style.Colors[ImGuiCol_TitleBgCollapsed] = GRAY400;
        style.Colors[ImGuiCol_MenuBarBg] = GRAY100;
        style.Colors[ImGuiCol_ScrollbarBg] = GRAY100; // same as regular background
        style.Colors[ImGuiCol_ScrollbarGrab] = GRAY400;
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = GRAY600;
        style.Colors[ImGuiCol_ScrollbarGrabActive] = GRAY700;
        style.Colors[ImGuiCol_CheckMark] = SEAFOAM500;
        style.Colors[ImGuiCol_SliderGrab] = GRAY700;
        style.Colors[ImGuiCol_SliderGrabActive] = GRAY800;
        style.Colors[ImGuiCol_Button] = SEAFOAM400;
        style.Colors[ImGuiCol_ButtonHovered] = SEAFOAM500;
        style.Colors[ImGuiCol_ButtonActive] = SEAFOAM700;
        style.Colors[ImGuiCol_Header] = SEAFOAM400;
        style.Colors[ImGuiCol_HeaderHovered] = SEAFOAM500;
        style.Colors[ImGuiCol_HeaderActive] = SEAFOAM600;
        style.Colors[ImGuiCol_Separator] = GRAY400;
        style.Colors[ImGuiCol_SeparatorHovered] = GRAY600;
        style.Colors[ImGuiCol_SeparatorActive] = GRAY700;
        style.Colors[ImGuiCol_ResizeGrip] = GRAY400;
        style.Colors[ImGuiCol_ResizeGripHovered] = GRAY600;
        style.Colors[ImGuiCol_ResizeGripActive] = GRAY700;
        style.Colors[ImGuiCol_PlotLines] = SEAFOAM400;
        style.Colors[ImGuiCol_PlotLinesHovered] = SEAFOAM600;
        style.Colors[ImGuiCol_PlotHistogram] = SEAFOAM400;
        style.Colors[ImGuiCol_PlotHistogramHovered] = SEAFOAM600;
        style.Colors[ImGuiCol_TextSelectedBg] = SEAFOAM600;
        style.Colors[ImGuiCol_DragDropTarget] = ORANGE;
        style.Colors[ImGuiCol_NavHighlight] = GRAY700;
        style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        }



    void StyleManager::loadStyle() {
        setupFonts();
        setupColors();
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 10; // rounded corners
        style.ItemSpacing = ImVec2(20, 20);

    }

    ImFont * StyleManager::getFont(Font const font) {
        return fontMap[font];
    }



} // commons

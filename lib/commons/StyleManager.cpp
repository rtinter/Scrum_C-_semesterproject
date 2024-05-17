#include "StyleManager.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include <sys/stat.h>
#include <iostream>

namespace commons {

    bool fileExists(const std::string &path) {
        struct stat buffer;
        return (stat(path.c_str(), &buffer) == 0);
    }

    std::map<Font, ImFont*> StyleManager::fontMap;

    void StyleManager::setupFonts(){

        ImGuiIO &io{ImGui::GetIO()};
        fontMap[Font::HEADER1] = io.Fonts->AddFontDefault();
        fontMap[Font::HEADER2] = io.Fonts->AddFontDefault();
        fontMap[Font::HEADER3] = io.Fonts->AddFontDefault();
        fontMap[Font::BODY] = io.Fonts->AddFontDefault();
        fontMap[Font::HEADER1]->Scale = 6.f;
        io.Fonts->Build();
        ImGui::SFML::UpdateFontTexture();

        // Load font from other source -> doesn't work
        float fontSize = 18.0f; // Set font size
        if (fileExists("Font.h")) {
            std::cout << "Die Datei existiert." << std::endl;
        } else {
            std::cout << "Die Datei existiert nicht." << std::endl;
        }
        //fontMap[Font::HEADER1] = io.Fonts->AddFontFromFileTTF("./Roboto-Medium.ttf", fontSize); // can be replaced with other font

    }

    void setupColors(){

        // Feel free to adjust and add more!
        ImVec4 primaryColor{0.25f, 0.67f, 0.75f, 1.f};
        ImVec4 secondaryColor{0.27f, 0.6f, 0.65f, 1.f};
        ImVec4 accentColor{0.25f, 0.8f, 0.81f, 1.f};
        ImVec4 backgroundColor{0.93f, 1.f, 0.95f, 1.f};
        ImVec4 textColor{0.05f, 0.1f, 0.09f, 1.f};
        ImVec4 infoColor{0.2f, 0.205f, 0.9f, 1.f};
        ImVec4 successColor{0.f, 0.63f, 0.f, 1.f};
        ImVec4 warningColor{0.82f, 0.75f, 0.f, 1.f};
        ImVec4 errorColor{0.82f, 0.31f, 0.f, 1.f};

        ImGuiStyle &style{ImGui::GetStyle()};

        //style.Colors[ImGuiCol_Button] = secondaryColor;
        //style.Colors[ImGuiCol_Border] = primaryColor;
        //style.Colors[ImGuiCol_BorderShadow] = secondaryColor;
        //style.Colors[ImGuiCol_FrameBg] = backgroundColor;
        style.Colors[ImGuiCol_WindowBg] = primaryColor;
        style.Colors[ImGuiCol_Text] = textColor;
        //style.Colors[ImGuiCol_ButtonHovered] = accentColor;
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

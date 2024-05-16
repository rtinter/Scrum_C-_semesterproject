//
// Created by zepi on 16.05.24.
//

#include "StyleManager.hpp"
#include "imgui.h"

void loadFonts(){
    ImGuiIO &io{ImGui::GetIO()};

    ImFont *bigFont{io.Fonts->AddFontDefault()};
    bigFont->Scale = 3.f;

    ImFont *veryBigFont{io.Fonts->AddFontDefault()};
    veryBigFont->Scale = 6.f;

    // Load font from other source
     float fontSize = 18.0f; // Set font size
     io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", fontSize); // can be replaced with other font

     /*
    Choose Font for you GUI-Element:
    ImGuiIO &io{ImGui::GetIO()};
    ImGui::PushFont(io.Fonts->Fonts[1]);
      */

}

namespace commons {
    void StyleManager::loadStyle() {
        loadFonts();
        ImGuiStyle &style{ImGui::GetStyle()};
        style.WindowRounding = 10;
        //style.Colors[ImGuiCol_Border] = ImVec4(0.2f, 0.205f, 0.9f, 1.00f);
        //style.ItemSpacing = ImVec2(20, 20);

    }


} // commons

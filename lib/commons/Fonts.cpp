#include "Fonts.hpp"
#include "imgui-SFML.h"

namespace commons {
    ImFont *Fonts::_body = nullptr;
    ImFont *Fonts::_header1 = nullptr;
    ImFont *Fonts::_header2 = nullptr;
    ImFont *Fonts::_header3 = nullptr;
    ImFont *Fonts::_matrixFontBig = nullptr;
    ImFont *Fonts::_matrixFontSmall = nullptr;

    void Fonts::setup() {
        ImGuiIO &io{ImGui::GetIO()};
        io.Fonts->Clear();
        // current working directory is athena/cmake-build-debug/bin
        _body = io.Fonts->AddFontFromFileTTF("Fonts/Roboto-Light.ttf", 25.0);
        _header1 = io.Fonts->AddFontFromFileTTF("Fonts/Roboto-Bold.ttf", 80.0);
        _header2 = io.Fonts->AddFontFromFileTTF("Fonts/Roboto-Medium.ttf", 40.0);
        _header3 = io.Fonts->AddFontFromFileTTF("Fonts/Roboto-Medium.ttf", 30.0);
        _matrixFontBig = io.Fonts->AddFontFromFileTTF("Fonts/Elite Hacker (Corroded).ttf", 30.0);
        _matrixFontSmall = io.Fonts->AddFontFromFileTTF("Fonts/Elite Hacker (Corroded).ttf", 20.0);
        io.Fonts->Build();
        ImGui::SFML::UpdateFontTexture();
    }

} // commons
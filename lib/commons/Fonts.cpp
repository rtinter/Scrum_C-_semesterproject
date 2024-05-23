#include "Fonts.hpp"
#include "imgui-SFML.h"

namespace commons {
    ImFont *Fonts::_body = nullptr;
    ImFont *Fonts::_header1 = nullptr;
    ImFont *Fonts::_header2 = nullptr;
    ImFont *Fonts::_header3 = nullptr;

    void Fonts::setup() {
        ImGuiIO &io{ImGui::GetIO()};
        io.Fonts->Clear();
        // current working directory is athena/cmake-build-debug/bin
        _body = io.Fonts->AddFontFromFileTTF("../../lib/commons/ttfFiles/Roboto-Light.ttf", 25.0);
        _header1 = io.Fonts->AddFontFromFileTTF("../../lib/commons/ttfFiles/Roboto-Bold.ttf", 80.0);
        _header2 = io.Fonts->AddFontFromFileTTF("../../lib/commons/ttfFiles/Roboto-Medium.ttf", 40.0);
        _header3 = io.Fonts->AddFontFromFileTTF("../../lib/commons/ttfFiles/Roboto-Medium.ttf", 30.0);
        io.Fonts->Build();
        ImGui::SFML::UpdateFontTexture();
    }

} // commons
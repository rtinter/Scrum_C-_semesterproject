#include "Fonts.hpp"
#include "imgui-SFML.h"

namespace commons {
    ImFont *Fonts::_body = nullptr;
    ImFont *Fonts::_header1 = nullptr;
    ImFont *Fonts::_header2 = nullptr;
    ImFont *Fonts::_header3 = nullptr;
    ImFont *Fonts::_iconRegular = nullptr;
    ImFont *Fonts::_iconSolid = nullptr;
    ImFont *Fonts::_matrixFontBig = nullptr;
    ImFont *Fonts::_matrixFontSmall = nullptr;

    void Fonts::setup() {
        ImGuiIO &io{ImGui::GetIO()};
        io.Fonts->Clear();
        // current working directory is athena/cmake-build-debug/bin
        _body = io.Fonts->AddFontFromFileTTF("Fonts/NotoSansNerdFont-Regular.ttf", 25.0);
        _header1 = io.Fonts->AddFontFromFileTTF("Fonts/NotoSansNerdFont-Bold.ttf", 80.0);
        _header2 = io.Fonts->AddFontFromFileTTF("Fonts/NotoSansNerdFont-Medium.ttf", 40.0);
        _header3 = io.Fonts->AddFontFromFileTTF("Fonts/NotoSansNerdFont-Medium.ttf", 30.0);
        _matrixFontBig = io.Fonts->AddFontFromFileTTF("Fonts/Elite Hacker (Corroded).ttf", 50.0);
        _matrixFontSmall = io.Fonts->AddFontFromFileTTF("Fonts/Elite Hacker (Corroded).ttf", 25.0);

        static constexpr ImWchar ICONS_RANGE[] = {0x1, 0xffff, 0};
        static ImFontConfig iconsConfig;
        iconsConfig.OversampleH = iconsConfig.OversampleV = 1;
        iconsConfig.MergeMode = true;

        _iconRegular = io.Fonts->AddFontFromFileTTF("Fonts/fa-regular-400.ttf", 50.0);
        _iconSolid = io.Fonts->AddFontFromFileTTF("Fonts/fa-solid-900.ttf", 50.0, &iconsConfig, ICONS_RANGE);
        io.Fonts->Build();
        ImGui::SFML::UpdateFontTexture();
    }

} // commons

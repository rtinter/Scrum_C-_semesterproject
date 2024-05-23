#include "Header.hpp"
#include <utility>
#include "Window.hpp"
#include "Fonts.hpp"

Header::Header(std::string left, std::string right, std::function<void()> callback)
        : _leftText(std::move(left)), _rightButtonText(std::move(right)), _buttonClickCallback(std::move(callback)) {
    _centerText = "Athena";
}

void Header::render() {
    ui_elements::Window("Header").render([this]() {
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, kHEADER_HEIGHT + kTOP_MARGIN + kBOTTOM_MARGIN),
                             ImGuiCond_Always);

        // Vertikale Abstände
        ImGui::SetCursorPosY(kTOP_MARGIN);

        // Vertikale Abstände
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + kBOTTOM_MARGIN);


        // Linker Text
        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::SetCursorPosX(kSIDE_MARGIN);
        ImGui::Text("%s", _leftText.c_str());

        // Zentraler Text
        ImGui::SameLine(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(_centerText.c_str()).x / 2);
        ImGui::Text("%s", _centerText.c_str());

        // Rechter Button mit Margin
        ImGui::SameLine(ImGui::GetIO().DisplaySize.x - ImGui::CalcTextSize(_rightButtonText.c_str()).x - kSIDE_MARGIN);
        if (ImGui::Button(_rightButtonText.c_str())) {
            if (_buttonClickCallback) {
                _buttonClickCallback();
            }
        }
        ImGui::PopFont();
    });
}

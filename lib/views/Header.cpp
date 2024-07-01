#include "Header.hpp"

#include "Fonts.hpp"
#include "Window.hpp"


namespace views {
    Header::Header(std::string const &left, std::string const &right, std::function<void()> const &callback)
        : _leftText(left), _rightButtonText(right), _buttonClickCallback(callback) {
        _centerText = "Athena";
    }

    void Header::render() const {
        ui_elements::Window("Header").render([this] {
            ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, HEADER_HEIGHT + TOP_MARGIN),
                                 ImGuiCond_Always);

            // Vertikale Abstände
            ImGui::SetCursorPosY(TOP_MARGIN);

            // Linker Text
            ImGui::PushFont(commons::Fonts::_header3);
            ImGui::SetCursorPosX(SIDE_MARGIN);
            ImGui::Text("%s", _leftText.c_str());

            // Zentraler Text
            ImGui::SameLine(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(_centerText.c_str()).x / 2);
            ImGui::Text("%s", _centerText.c_str());

            // Rechter Button mit Margin
            ImGui::SameLine(
                ImGui::GetIO().DisplaySize.x - ImGui::CalcTextSize(_rightButtonText.c_str()).x - SIDE_MARGIN);
            if (ImGui::Button(_rightButtonText.c_str())) {
                if (_buttonClickCallback) {
                    _buttonClickCallback();
                }
            }
            ImGui::PopFont();

            ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x,
                                            ImGui::GetIO().DisplaySize.y - (HEADER_HEIGHT + TOP_MARGIN)));
            ImGui::SetNextWindowPos(ImVec2(0, HEADER_HEIGHT + TOP_MARGIN));
        });
    }
} // views

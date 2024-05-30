#include "Tile.hpp"
#include "../commons/Fonts.hpp"
#include "Window.hpp"
#include <sstream>
#include <utility>

#pragma once

namespace ui_elements {

    // Konstruktor
    Tile::Tile(std::string const &pic, std::string const &name, std::string const &desc,
               std::function<void()> const &onClick)
            : _pictogram(pic), _gameName(name), _description(desc), _onClick(onClick) {
        setButtonText();
    }

    // Setter-Methode für den Button-Text
    void Tile::setButtonText() {
        std::stringstream ss;
        ss << _pictogram << "\n" << _gameName << "\n" << _description;
        _buttonText = ss.str();
    }

    // Render-Methode
    void Tile::render() const {
        ui_elements::Window("Dashboard").render([this]() {
            ImGui::SetWindowPos(ImVec2(0, 50), ImGuiCond_Always);
            ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50),
                                 ImGuiCond_Always);

            ImGui::PushFont(commons::Fonts::_header2);
            if (ImGui::Button(_buttonText.c_str(), ImVec2(this->_width, this->_height))) {
                if (_onClick) {
                    _onClick();
                }
            }
            ImGui::PopFont();
        });
    }
}




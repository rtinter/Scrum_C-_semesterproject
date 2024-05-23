#include "Tile.hpp"
#include "../commons/Fonts.hpp"
#include "Window.hpp"
#include <sstream>
#include <utility>

#pragma once

namespace ui_elements {

// Konstruktor
    Tile::Tile(std::string pic, std::string name, std::string desc)
            : _pictogram(std::move(pic)), _gameName(std::move(name)), _description(std::move(desc)) {
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
                // Button action
            }
            ImGui::PopFont();
        });
    }
}




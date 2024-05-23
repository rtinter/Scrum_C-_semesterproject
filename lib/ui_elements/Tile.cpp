#include "Tile.hpp"
#include <sstream>
#pragma once

namespace ui_elements {

// Konstruktor
    Tile::Tile(const std::string& pic, const std::string& name, const std::string& desc)
            :pictogram(pic), gameName(name), description(desc) {
        setButtonText();
    }

// Setter-Methode für den Button-Text
    void Tile::setButtonText() {
        std::stringstream ss;
        ss << pictogram << "\n" << gameName << "\n" << description;
        buttonText = ss.str();
    }

// Render-Methode
    void Tile::render() const{
        ImGui::Begin("Dashboard", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration);
        ImGui::SetWindowPos(ImVec2(0, 50), ImGuiCond_Always);
        ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50), ImGuiCond_Always);

        if (ImGui::Button(buttonText.c_str(), ImVec2(this->width, this->height))) {
            // Button action
        }

        ImGui::End();
    }

}

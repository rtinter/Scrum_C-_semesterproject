//
// Created by samtf on 07.06.2024.
//

#include "TableContainer.h"
#include "Window.hpp"
#include "Fonts.hpp"

namespace ui_elements {

    TableContainer::TableContainer(std::string const &gameName) : _gameName(gameName) {

    }



    void TableContainer::render() const {
        ui_elements::Window("TableContainer").render([this](){
            ImGui::SetWindowPos(ImVec2(0, 100), ImGuiCond_Always);
            ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50),
                                 ImGuiCond_Always);
            ImGui::PushFont(commons::Fonts::_header2);
            ImGui::Text(_gameName.c_str());
            ImGui::PopFont();
        });
    }
} // ui_elements
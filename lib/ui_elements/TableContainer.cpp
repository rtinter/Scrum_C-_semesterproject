#include "TableContainer.h"

#include <Colors.hpp>
#include <iostream>

#include "imgui_internal.h"
#include "Window.hpp"
#include "Fonts.hpp"

namespace ui_elements {

    TableContainer::TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable)
            : _gameName{gameName}, _statisticsGameTable{statisticsGameTable} {}


    void TableContainer::render() {

        float childWidth{ImGui::GetContentRegionAvail().x * 0.5f};
        float childHeight{400.f};

        ImGui::BeginChild(_gameName.c_str(), ImVec2(childWidth, childHeight), true, ImGuiWindowFlags_AlwaysAutoResize);
       ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::DARK_GRAY);

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::Text("Spiel %s", _gameName.c_str());

        _statisticsGameTable.render();


        ImGui::PopStyleColor();
        ImGui::PopFont();
        ImGui::EndChild();
    }
} // ui_elements
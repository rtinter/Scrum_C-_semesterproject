#include "TableContainer.h"


#include "Window.hpp"
#include "Fonts.hpp"

namespace ui_elements {

    TableContainer::TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable)
            : _gameName{gameName}, _statisticsGameTable{statisticsGameTable} {}


    void TableContainer::render() {

        float childWidth{600.f};
        float childHeight{400.f};

        ImGui::BeginChild(_gameName.c_str(), ImVec2(childWidth, childHeight), true, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::Text("Spiel %s", _gameName.c_str());

        _statisticsGameTable.render();


        ImGui::EndChild();
    }
} // ui_elements
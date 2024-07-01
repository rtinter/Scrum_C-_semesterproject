#include "TableContainer.hpp"

#include "Fonts.hpp"
#include "Window.hpp"

namespace ui_elements {
    TableContainer::TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable)
        : _gameName{gameName}, _statisticsGameTable{statisticsGameTable} {
    }


    void TableContainer::render() {
        float const childWidth{(ImGui::GetWindowWidth() / 2) - 20.f};
        constexpr float CHILD_HEIGHT{400.f};

        ImGui::BeginChild(_gameName.c_str(), ImVec2(childWidth, CHILD_HEIGHT), true, ImGuiWindowFlags_AlwaysAutoResize);

        ImGui::PushFont(commons::Fonts::_header2);
        ImGui::Text("Spiel %s", _gameName.c_str());
        ImGui::PopFont();

        _statisticsGameTable.render();


        ImGui::EndChild();
    }
} // ui_elements

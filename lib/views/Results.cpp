#include "Results.h"
#include "Window.hpp"
#include "StatisticsGameTable.hpp"
#include <imgui.h>

namespace views {

    void Results::render() {
        ui_elements::Window("Results").render([this](){

            int count = 0;
            for (const ui_elements::TableContainer &tableContainer : _gameTableContainers)
            {
                if (count > 0 && count % 2 == 0) {
                    ImGui::NewLine();
                }
                tableContainer.render();
                if (count % 2 == 0) {
                    ImGui::SameLine();
                }
                ++count;
            }
        });
    }

    void Results::addGameTableContainer(const ui_elements::TableContainer &tableContainer) {
        _gameTableContainers.emplace_back(tableContainer);
    }

    void Results::addGameTableContainers(const std::vector<ui_elements::TableContainer> &tableContainers) {
        for (const auto &tableContainer : tableContainers) {
            addGameTableContainer(tableContainer);
        }
    }
} // views
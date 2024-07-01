#include "Results.hpp"
#include "Window.hpp"
#include <imgui.h>

namespace views {

    void Results::render() {
        ui_elements::Window("Results").render([this] {
            ImGui::SetWindowPos(ImVec2(0, 100));
            ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50));

            int count{0};
            for (ui_elements::TableContainer &tableContainer: _gameTableContainers) {
                if (count > 0 && count % 2 == 0) {
                    ImGui::NewLine();
                }
                tableContainer.render();
                if (count % 2 == 0) {
                    ImGui::SameLine();
                }
                ++count;
            }
            ImGui::NewLine();
            ImGui::NewLine();
        });
    }

    void Results::addGameTableContainer(ui_elements::TableContainer const &tableContainer) {
        _gameTableContainers.emplace_back(tableContainer);
    }
} // views
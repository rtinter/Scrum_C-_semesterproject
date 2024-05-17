#include "Dashboard.hpp"
#include <imgui.h>

#include "Window.hpp"

namespace views {

    void Dashboard::addTileToCategory1(const ui_elements::Tile &tile) {
        _category1Tiles.emplace_back(tile);
    }

    void Dashboard::addTileToCategory2(const ui_elements::Tile &tile) {
        _category2Tiles.emplace_back(tile);
    }

    void Dashboard::render() {
        ui_elements::Window("Dashboard").render([this]() {

            //  Render Category 1
            ImGui::Text("Kategorie 1");
            ImGui::Spacing();
            ImGui::Spacing();
            for (int i = 0; i < _category1Tiles.size(); ++i) {
                if (i > 0 && i % 2 == 0) {
                    ImGui::NewLine();
                }
                _category1Tiles[i].render();
                if (i % 2 == 0) {
                    ImGui::SameLine();
                }
            }
            ImGui::NewLine();


            // Render Category 2
            ImGui::Text("Kategorie 2");
            ImGui::Spacing();
            ImGui::Spacing();
            for (int i = 0; i < _category2Tiles.size(); ++i) {
                if (i > 0 && i % 2 == 0) {
                    ImGui::NewLine();
                }
                _category2Tiles[i].render();
                if (i % 2 == 0) {
                    ImGui::SameLine();
                }
            }
            ImGui::NewLine();
        });
    }
}

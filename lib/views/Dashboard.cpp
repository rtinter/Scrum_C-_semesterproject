#include "Dashboard.hpp"
#include <imgui.h>
#include "Window.hpp"
#include "Fonts.hpp"

namespace views {

    void Dashboard::addTileToCategory1(const ui_elements::Tile &tile) {
        _category1Tiles.emplace_back(tile);
    }

    void Dashboard::addTileToCategory2(const ui_elements::Tile &tile) {
        _category2Tiles.emplace_back(tile);
    }

    void Dashboard::renderCategory(const std::string &categoryName, const std::vector<ui_elements::Tile> &tiles) const {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::Text("%s", categoryName.c_str());
        ImGui::PopFont();

        ImGui::Spacing();
        ImGui::Spacing();
        for (int i = 0; i < tiles.size(); ++i) {
            if (i > 0 && i % 2 == 0) {
                ImGui::NewLine();
            }
            tiles[i].render();
            if (i % 2 == 0) {
                ImGui::SameLine();
            }
        }
        ImGui::NewLine();
    }

    void Dashboard::render() const {
        ui_elements::Window("Dashboard").render([this]() {
            renderCategory("Kategorie 1", _category1Tiles);
            renderCategory("Kategorie 2", _category2Tiles);
        });
    }


}

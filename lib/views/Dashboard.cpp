#include "Dashboard.hpp"
#include <imgui.h>
#include "Window.hpp"
#include "Fonts.hpp"
#include <memory>

namespace {
    
    void renderCategory(const std::string &categoryName, const std::vector<ui_elements::Tile> &tiles) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::Text("%s", categoryName.c_str());
        ImGui::PopFont();

        ImGui::Spacing();
        ImGui::Spacing();
        
        int count = 0;
        for (const auto& tile : tiles) {
            if (count > 0 && count % 2 == 0) {
                ImGui::NewLine();
            }
            tile.render();
            if (count % 2 == 0) {
                ImGui::SameLine();
            }
            ++count;
        }
        ImGui::NewLine();
    }
}

namespace views {

    void Dashboard::addTileToCategory(const std::string& category, const ui_elements::Tile &tile) {
        _categoryTiles[category].emplace_back(tile);
    }
    //add tiles to category
    void Dashboard::addTilesToCategory(const std::string& category, const std::vector<ui_elements::Tile>& tiles) {
        for (const auto& tile : tiles) {
            addTileToCategory(category, tile);
        }
    }


    void Dashboard::render() {
        ui_elements::Window("Dashboard").render([this]() {
            for (const auto& category : _categoryTiles) {
                renderCategory(category.first, category.second);
            }
        });
    }
}

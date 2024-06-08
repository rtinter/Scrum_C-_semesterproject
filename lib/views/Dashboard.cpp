#include "Dashboard.hpp"
#include "Fonts.hpp"
#include "Window.hpp"
#include <imgui.h>

namespace {

void renderCategory(const String &categoryName,
                    std::vector<UniqueTile> &tiles) {
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::PushFont(commons::Fonts::_header3);
    ImGui::Text("%s", categoryName.c_str());
    ImGui::PopFont();

    ImGui::Spacing();
    ImGui::Spacing();

    int count = 0;
    for (UniqueTile &tile : tiles) {
        if (count > 0 && count % 2 == 0) {
            ImGui::NewLine();
        }
        if (tile)
            tile->render();
        if (count % 2 == 0) {
            ImGui::SameLine();
        }
        ++count;
    }
    ImGui::NewLine();
}
}

namespace views {

void Dashboard::addTileToCategory(const std::string &category,
                                  UniqueTile &tile) {
    _categoryTiles[category].push_back(std::move(tile));
}

//add tiles to category
void Dashboard::addTilesToCategory(const std::string &category,
                                   std::vector<UniqueTile> &tiles) {
    for (auto &tile : tiles) {
        addTileToCategory(category, tile);
    }
}

void Dashboard::render() {
    ui_elements::Window("Dashboard").render([this]() {
      for (auto &category : _categoryTiles) {
          renderCategory(category.first, category.second);
      }
    });
}
}

#include "Dashboard.hpp"

#include <Centered.hpp>


#include "Fonts.hpp"
#include "Window.hpp"
#include <imgui.h>
#include <TextCentered.hpp>


namespace {
    void renderCategory(const String &categoryName, std::vector<UniqueTile> &tiles) {
        ImGui::Spacing();

        ImGui::PushFont(commons::Fonts::_header1);
        ui_elements::TextCentered(categoryName.c_str());
        ImGui::PopFont();


        ui_elements::Centered([&tiles] {
            int count = 0;
            for (UniqueTile &tile: tiles) {
                count++;
                if (tile)
                    tile->render();
                if (count == 4) {
                    ImGui::NewLine();
                    count = 0;
                } else {
                    ImGui::SameLine();
                }
            }
        });
    }
}

namespace views {
    void Dashboard::addTileToCategory(const std::string &category,
                                      UniqueTile &tile) {
        _categoryTiles[category].push_back(std::move(tile));
    }

    //add tiles to category
    void Dashboard::addTilesToCategory(const std::string &category, std::vector<UniqueTile> &tiles) {
        for (auto &tile: tiles) {
            addTileToCategory(category, tile);
        }
    }

    void Dashboard::render() {
        ui_elements::Window("Dashboard").render([this]() {
            for (auto &category: _categoryTiles) {
                renderCategory(category.first, category.second);
            }
        });
    }
}

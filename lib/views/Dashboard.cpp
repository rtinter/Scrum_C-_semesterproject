#include "Dashboard.hpp"
#include <imgui.h>

void Dashboard::addTileToCategory1(const ui_elements::Tile& tile) {
    category1Tiles.emplace_back(tile);
}

void Dashboard::addTileToCategory2(const ui_elements::Tile& tile) {
    category2Tiles.emplace_back(tile);
}

void Dashboard::render() {
    ImGui::Begin("Dashboard", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(0, 50), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50), ImGuiCond_Always);

    // Render Category 1
    ImGui::Text("Kategorie 1");
    ImGui::Spacing();
    ImGui::Spacing();
    for (int i = 0; i < category1Tiles.size(); ++i) {
        if (i > 0 && i % 2 == 0) {
            ImGui::NewLine();
        }
        category1Tiles[i].render();
        if (i % 2 == 0) {
            ImGui::SameLine();
        }
    }
    ImGui::NewLine();

    // Render Category 2
    ImGui::Text("Kategorie 2");
    ImGui::Spacing();
    ImGui::Spacing();
    for (int i = 0; i < category2Tiles.size(); ++i) {
        if (i > 0 && i % 2 == 0) {
            ImGui::NewLine();
        }
        category2Tiles[i].render();
        if (i % 2 == 0) {
            ImGui::SameLine();
        }
    }
    ImGui::NewLine();

    ImGui::End();
}

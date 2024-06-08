//
// Created by benni on 08.06.2024.
//

#include "LetterSalad.hpp"
#include "Window.hpp"
#include "Centered.hpp"

namespace game {

std::string LetterSalad::getName() const {
    return "Letter Salad";
}

void LetterSalad::render() {
    ui_elements::Window("LetterSalad Game").render([this]() {
      ui_elements::Centered([this]() {
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,
                            ImVec2(0.5f, 0.5f));

        for (int y = 0; y < _gameField.size(); y++) {
            auto &row = _gameField[y];

            for (int x = 0; x < row.size(); x++) {
                // Always print on the same line but the first cell
                if (x > 0) ImGui::SameLine();

                // PushID is used to ensure that each cell has a unique ID
                ImGui::PushID(y * 20+x);
                if (ImGui::Selectable(_gameField[y][x].first.c_str(),
                                      _gameField[y][x].second,
                                      0,
                                      ImVec2(20, 20))) {

                    // Toggle clicked cell
                    _gameField[y][x].second ^= 1;
                }
                ImGui::PopID();
            }
        }
        ImGui::PopStyleVar();
      });
    });
}

void LetterSalad::renderGame() {

}

void LetterSalad::update() {

}

void LetterSalad::stop() {
    Game::stop();
}
void LetterSalad::start() {

}
void LetterSalad::reset() {

}
void LetterSalad::updateStatistics() {

}

} // namespace game
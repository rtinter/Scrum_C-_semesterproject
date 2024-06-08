//
// Created by Benjamin Puhani on 08.06.2024.
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
                    // Toggle clicked cell if clicked
                    clickCell({y, x});
                }
                ImGui::PopID();
            }
        }
        ImGui::PopStyleVar();
      });
    });
}

void LetterSalad::clickCell(Coordinates coords) {
    _gameField[coords.y][coords.x].second ^= 1;

    // if the first has not been selected yet
    if (!_isFirstCellSelected) {
        // then this is the first cell selected
        _isFirstCellSelected = true;
    } else if (!_isSecondCellSelected) {
        // if the first cell has been selected
        // then this is the second cell selected
        _isSecondCellSelected = true;
        pairSelected();
        resetSelectedPair();
    }

}

void LetterSalad::resetSelectedPair() {
    _isFirstCellSelected = false;
    _firstSelectedCell = {-1, -1};
    _isSecondCellSelected = false;
    _secondSelectedCell = {-1, -1};
}

/**
 * Get the coordinates of the cells between the start and end cell.
 * Diagonally, horizontally or vertically.
 */
std::vector<Coordinates> getLine(Coordinates start, Coordinates end) {

}

void LetterSalad::pairSelected() {
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
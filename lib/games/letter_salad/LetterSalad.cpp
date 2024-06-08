//
// Created by Benjamin Puhani on 08.06.2024.
//

#include <iostream>
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
        _firstSelectedCell = coords;
    } else if (!_isSecondCellSelected) {
        // if the first cell has been selected
        // then this is the second cell selected
        _isSecondCellSelected = true;
        _secondSelectedCell = coords;
        pairSelected();
        for (auto &lineE : getLine(_firstSelectedCell, _secondSelectedCell)) {
            selectBox(lineE);
        }
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
 * Basing on the Bresenham's line algorithm.
 */
std::vector<Coordinates> LetterSalad::getLine(Coordinates &start,
                                              Coordinates &end) {
    std::vector<Coordinates> linePoints;
    int x1{start.x};
    int y1{start.y};
    int x2{end.x};
    int y2{end.y};

    int dx{std::abs(x2-x1)};
    int sx{x1 < x2 ? 1 : -1};
    int dy{-std::abs(y2-y1)};
    int sy{y1 < y2 ? 1 : -1};
    int err{dx+dy};
    int e2; // Fehlerwert e_xy

    while (true) {
        // Fügt den aktuellen Punkt zur Liste hinzu
        linePoints.emplace_back(y1, x1);
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) { // Fehler akkumulierte sich in horizontaler Richtung
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) { // Fehler akkumulierte sich in vertikaler Richtung
            err += dx;
            y1 += sy;
        }
    }
    return linePoints;
}

void LetterSalad::selectBox(Coordinates &coords) {
    if (coords.x < 0 || coords.y < 0 || coords.x >= 20 || coords.y >= 20) {
        std::cerr << "Invalid coordinates" << std::endl;
        std::cerr << coords.y << " " << coords.x << std::endl;
        return;
    }
    _gameField[coords.y][coords.x].second = true;
}

void LetterSalad::deSelectBox(Coordinates &coords) {
    if (coords.x < 0 || coords.y < 0 || coords.x >= 20 || coords.y >= 20) {
        std::cerr << "Invalid coordinates" << std::endl;
        std::cerr << coords.y << " " << coords.x << std::endl;
        return;
    }
    _gameField[coords.y][coords.x].second = false;
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
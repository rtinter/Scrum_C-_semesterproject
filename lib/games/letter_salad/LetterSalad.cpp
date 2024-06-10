//
// Created by Benjamin Puhani on 08.06.2024.
//

#include <iostream>
#include "LetterSalad.hpp"
#include "Window.hpp"
#include "Centered.hpp"
#include <algorithm>
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "imgui_internal.h"

#define EMPTY_CELL "_"

namespace game {

std::string LetterSalad::getName() const {
    return "Letter Salad";
}

CharVector2D LetterSalad::_gameField = {20, {20, Box{EMPTY_CELL}}};
std::vector<Coordinates> LetterSalad::_currentLine = {};
std::vector<WordTarget> LetterSalad::_wordList = {
    {"Kreativitaet", false},
    {"Geschwindigkeit", false},
    {"Universum", false},
    {"Glueckseligkeit", false},
    {"Wasserfall", false},
    {"Bibliothek", false},
    {"Schmetterling", false},
    {"Konversation", false},
    {"Landschaft", false},
    {"Sonnenuntergang", false},
    {"Hoffnungsschimmer", false},
    {"Sternschnuppe", false},
    {"Gluehbirne", false},
    {"Flugzeug", false},
    {"Wissenschaft", false},
    {"Diskothek", false},
    {"Traumfaenger", false},
    {"Zirkuszelt", false},
    {"Schokolade", false},
    {"Gemeinschaft", false}
};

void LetterSalad::render() {

    if (_gameField[0][0].getLetter() == EMPTY_CELL) {
        LetterSalad::randomizeGameField();
    }

    ui_elements::Window("LetterSalad Game").render([this]() {

      LetterSalad::renderTextList();
      ImGui::SameLine();
      this->renderGameField();
      this->renderSelectedWord();

    });
}

void LetterSalad::onHover(Coordinates const &coords) {

    static Coordinates lastHoveredCell{-1, -1};

    auto newlines{getLine(_firstSelectedCell, coords)};

    if (newlines.empty()) {
        return;
    }

    // check if the hovered cell is not the last hovered cell
    if (lastHoveredCell.x != -1 && lastHoveredCell != coords) {
        std::vector<Coordinates> difference;
        // remove all elements that are now not hovered anymore
        std::set_difference(_currentLine.begin(), _currentLine.end(),
                            newlines.begin(), newlines.end(),
                            std::back_inserter(difference));
        for (auto &lineE : difference) {
            deSelectBox(lineE);
        }

    } else {
        _selectedWord = "";
        _currentLine = getLine(_firstSelectedCell, coords);

        for (auto &lineE : _currentLine) {
            selectBox(lineE);
            _selectedWord += _gameField[lineE.y][lineE.x].getChar();
        }
    }

    lastHoveredCell = coords;
}

void LetterSalad::clickCell(Coordinates const &coords) {

    // if the first has not been selected yet
    if (!_isFirstCellSelected) {
        // then this is the first cell selected
        _isFirstCellSelected = true;
        _firstSelectedCell = coords;
//        _selectedWord = _gameField[coords.y][coords.x].getChar();
        selectBox(coords);
    } else if (!_isSecondCellSelected) {
        // if the first cell has been selected
        // then this is the second cell selected
        _isSecondCellSelected = true;
        _secondSelectedCell = coords;
        pairSelected();
        for (auto &lineE : getLine(_firstSelectedCell, _secondSelectedCell)) {
            selectBox(lineE);
        }
        // check if the selected elements are correct, if not reset
        resetSelectedPair();
    }

}

void LetterSalad::renderTextList() {
    ImGui::BeginListBox("##textList",
                        ImVec2(300, ImGui::GetWindowHeight()-100));

    for (auto &wordPair : _wordList) {
        ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
        ImGui::Checkbox(wordPair.first.c_str(),
                        &wordPair.second);
        ImGui::PopItemFlag();
    }

    ImGui::EndListBox(); // ##textList
}

void LetterSalad::renderGameField() {
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2-360, 50));
    ImGui::BeginChild("##gameField",
                      ImVec2(720, 760));
    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,
                        ImVec2(0.5f, 0.5f));

    for (int y = 0; y < _gameField.size(); y++) {
        auto &row = _gameField[y];

        for (int x = 0; x < row.size(); x++) {
            // Always print on the same line but the first cell
            if (x > 0) ImGui::SameLine();

            // PushID is used to ensure that each cell has a unique ID
            ImGui::PushID(y * 20+x);
            if (ImGui::Selectable(_gameField[y][x].getChar(),
                                  _gameField[y][x].isSelected,
                                  ImGuiSelectableFlags_AllowOverlap,
                                  ImVec2(20, 20))) {
                // Toggle clicked cell if clicked
                clickCell({y, x});
            }

            // run if the first cell has been selected
            // and another cell is hovered
            if (_isFirstCellSelected && ImGui::IsItemHovered()) {
                onHover({y, x});
            }

            ImGui::BeginDisabled(true);
            ImGui::EndDisabled();

            ImGui::PopID();
        }
    }
    ImGui::PopStyleVar();
    ImGui::EndChild(); // ##gameField
}

void LetterSalad::renderSelectedWord() const {
    static int const WIDTH = 650;
    static int const HEIGHT = 40;

    ImVec2 startPos{
        ImVec2(ImGui::GetWindowWidth() / 2-static_cast<int>(WIDTH / 2), 810)
    };

    ImGui::PushFont(commons::Fonts::_header2);

    ImGui::SetCursorPos(startPos);
    ImGui::BeginChild("##selectedWord",
                      ImVec2(WIDTH, HEIGHT));

    // Get the position and size of the dummy
    ImVec2 pos = ImGui::GetItemRectMin();
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    ImU32 rectangle = IM_COL32(3, 161, 252, 255);
    float rounding = 25.f;

    drawList->AddRectFilled(pos,
                            ImVec2(pos.x+WIDTH, pos.y+HEIGHT),
                            rectangle,
                            rounding
    );

    ui_elements::TextCentered(_selectedWord.c_str());
    ImGui::PopFont();
    ImGui::EndChild(); // ##selectedWord
}

void LetterSalad::resetSelectedPair() {
    _selectedWord = "";
    _isFirstCellSelected = false;
    _isSecondCellSelected = false;

    if (!LetterSalad::isWordInList(_selectedWord)) {
        for (auto &lineE : getLine(_firstSelectedCell, _secondSelectedCell)) {
            LetterSalad::deSelectBox(lineE);
        }
    } else {
        for (auto &lineE : getLine(_firstSelectedCell, _secondSelectedCell)) {
            LetterSalad::finalize(lineE);
        }

    }

    _firstSelectedCell = {-1, -1};
    _secondSelectedCell = {-1, -1};
    _currentLine.clear();
}

bool LetterSalad::isWordInList(std::string const &word) {
    return std::any_of(_wordList.begin(), _wordList.end(),
                       [&word](WordTarget &wordTarget) {
                         if (wordTarget.first == word) {
                             wordTarget.second = true;
                             return true;
                         }
                         return false;
                       }
    );
}

/**
 * Get the coordinates of the cells between the start and end cell.
 * Diagonally, horizontally or vertically.
 * Basing on the Bresenham's line algorithm.
 */
std::vector<Coordinates> LetterSalad::getLine(Coordinates const &start,
                                              Coordinates const &end) {
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

    // make sure to only draw elements
    // if the start and end cell are in one line
    // diagonally or horizontally or vertically
    bool isDiagonal = {std::abs(dx) == std::abs(dy)};
    bool isHorizontal = {dy == 0};
    bool isVertical = {dx == 0};

    // return if the cells are not in one line
    if (!isDiagonal && !isHorizontal && !isVertical) {
        return linePoints;
    }

    while (true) {
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

void LetterSalad::selectBox(Coordinates const &coords) {
    if (coords.x < 0 || coords.y < 0 || coords.x >= 20 || coords.y >= 20) {
        std::cerr << "Invalid coordinates" << std::endl;
        std::cerr << coords.y << " " << coords.x << std::endl;
        return;
    }
    _gameField[coords.y][coords.x].isSelected = true;
}

void LetterSalad::deSelectBox(Coordinates const &coords) {
    if (coords.x < 0 || coords.y < 0 || coords.x >= 20 || coords.y >= 20) {
        std::cerr << "Invalid coordinates" << std::endl;
        std::cerr << coords.y << " " << coords.x << std::endl;
        return;
    }
    _gameField[coords.y][coords.x].isSelected = false;
}

void LetterSalad::finalize(Coordinates const &coords) {
    if (coords.x < 0 || coords.y < 0 || coords.x >= 20 || coords.y >= 20) {
        std::cerr << "Invalid coordinates" << std::endl;
        std::cerr << coords.y << " " << coords.x << std::endl;
        return;
    }
    _gameField[coords.y][coords.x].isSolved = true;
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
void LetterSalad::randomizeGameField() {
    for (auto &row : _gameField) {
        for (auto &box : row) {
            // TODO @bpuhani check if an field already has a letter
            std::string letter{std::string(1, 'A'+rand() % 26)};
            box.setLetter(letter);
        }
    }
}

} // namespace game
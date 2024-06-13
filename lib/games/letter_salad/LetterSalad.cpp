//
// Created by Benjamin Puhani (941077) on 08.06.2024.
// &22 Buchstabensalat
//

#include <iostream>
#include "LetterSalad.hpp"
#include "Window.hpp"
#include <algorithm>
#include <random>
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "imgui_internal.h"
#include "Orientation.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "Centered.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"

namespace game {

std::random_device rd;
std::mt19937 gen(rd());

std::string LetterSalad::_gameName = "Buchstaben Salat";
std::string LetterSalad::_gameDescription = "Finde die versteckten Wörter im "
                                            "Buchstaben Salat.";
std::string
    LetterSalad::_gameRules = "Du hast 15min Zeit alle Wörter zu finden.";
std::string LetterSalad::_gameControls = "Klicke auf den ersten und letzten "
                                         "Buchstaben eines Wortes um es zu "
                                         "markieren.\nDie gefundenen Wörter"
                                         " erscheinen links in der Liste";

std::string LetterSalad::getName() const {
    return _gameName;
}

void LetterSalad::stop() {
    _showEndbox = true;
    _isGameRunning = false;
}

void LetterSalad::start() {
    getRandomWords();
    fillGameFieldWithWordlist();
    randomizeGameField();
    _isGameRunning = true;
    _showInfobox = false;
    _showEndbox = false;
    _timer.start();
}

void LetterSalad::reset() {
    _activeWordList.clear();
    _gameField.clear();
    _timer.reset();
    init();
    start();
}

void LetterSalad::init() {
    for (int y{0}; y < 20; y++) {
        std::vector<std::unique_ptr<Box>> row;
        for (int x{0}; x < 20; x++) {
            row.emplace_back(std::make_unique<Box>(EMPTY_CELL));
        }
        _gameField.emplace_back(std::move(row));
    }
    _isGameInitialized = true;
}
void LetterSalad::updateStatistics() {

}

std::vector<WordTarget> LetterSalad::_wordList = {
    WordTarget{"KREATIV"},
    WordTarget{"GESCHWINDIGKEIT"},
    WordTarget{"UNIVERSUM"},
    WordTarget{"GLUECK"},
    WordTarget{"WASSER"},
    WordTarget{"BIBLIOTHEK"},
    WordTarget{"KONVERSATION"},
    WordTarget{"LAND"},
    WordTarget{"SONNE"},
    WordTarget{"HOFFNUNG"},
    WordTarget{"GLUEHBIRNE"},
    WordTarget{"FLUGZEUG"},
    WordTarget{"WISSENSCHAFT"},
    WordTarget{"DISKOTHEK"},
    WordTarget{"ZIRKUS"},
    WordTarget{"TRAUM"},
    WordTarget{"SCHOKOLADE"},
    WordTarget{"GEMEINSCHAFT"},
    WordTarget{"KUNST"},
    WordTarget{"KULTUR"},
    WordTarget{"FRIEDEN"},
    WordTarget{"FREIHEIT"},
    WordTarget{"GESUNDHEIT"},
    WordTarget{"GELD"},
    WordTarget{"GESELLSCHAFT"},
    WordTarget{"GESCHICHTE"},
    WordTarget{"GLAUBE"},
    WordTarget{"GRENZE"},
    WordTarget{"GRENZUEBERGANG"},
    WordTarget{"GRENZUEBERSCHREITUNG"},
};

void LetterSalad::render() {

    if (!_isGameInitialized) {
        init();
        return;
    }

    ui_elements::InfoBox(
        _gameID,
        _showInfobox,
        _gameName.c_str(),
        _gameDescription.c_str(),
        _gameRules.c_str(),
        _gameControls.c_str(),
        [this] {
          start();
        }).render();

    if (_isGameRunning) {
        renderGame();
    }

    if (_showEndbox) {
        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
          ImGui::PushFont(commons::Fonts::_header2);
          ui_elements::TextCentered(std::move(_endboxTitle));
          ImGui::PopFont();
          ui_elements::TextCentered(std::move(_endboxText));

          ui_elements::Centered([this]() {
            if (ImGui::Button("Versuch es nochmal")) {
                reset();
            }

            if (ImGui::Button("Zurück zur Startseite")) {
                scene::SceneManager::getInstance().switchTo(std::make_unique<
                    scene::DashboardScene>());
            }
          });
        });
    }
}

void LetterSalad::renderGame() {
    ui_elements::Window("###letterSalad").render([this]() {

      _timer.render();
      LetterSalad::renderTextList();
      ImGui::SameLine();
      this->renderGameField();
      this->renderSelectedWord();
    });

    if (_timer.isExpiredNow()) {
        _endboxTitle = "Die Zeit ist abgelaufen!";

        int missingWords{0};
        int missingLetters{0};
        // get the number of words that are still missing
        for (auto const &wordTarget : _activeWordList) {
            if (!(*(wordTarget.isFound()))) {
                missingWords++;
                missingLetters += wordTarget.getWord().size();
            }
        }
        static std::string missingWordsText = "Dir fehlen noch\n"+
            std::to_string(missingWords)+" Wörter\nBzw. "+
            std::to_string(missingLetters)+" Buchstaben.";
        _endboxText = missingWordsText.c_str();
        stop();
    }
}

void LetterSalad::renderTextList() {
    if (ImGui::BeginListBox("##textList",
                            ImVec2(350, 900))) {
        for (auto const &wordPair : _activeWordList) {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::Checkbox(wordPair.getWord().c_str(), wordPair.isFound());
            ImGui::PopItemFlag();
        }

        ImGui::EndListBox(); // ##textList
    }

}

void LetterSalad::renderGameField() {
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2-360, 50));
    ImGui::BeginChild("##gameField", ImVec2(720, 760));
    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign,
                        ImVec2(0.5f, 0.5f)
    );

    for (int y = 0; y < _gameField.size(); y++) {
        auto &row = _gameField[y];

        for (int x = 0; x < row.size(); x++) {
            // Always print on the same line but the first cell
            if (x > 0) ImGui::SameLine();

            // PushID is used to ensure that each cell has a unique ID
            ImGui::PushID(y * 20+x);
            if (ImGui::Selectable(_gameField[y][x]->getChar(),
                                  _gameField[y][x]->isSelected ||
                                      _gameField[y][x]->isSolved,
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
            _selectedWord += _gameField[lineE.y][lineE.x]->getChar();
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
        selectBox(coords);
    } else if (!_isSecondCellSelected) {
        // if the first cell has been selected
        // then this is the second cell selected
        _isSecondCellSelected = true;
        _secondSelectedCell = coords;
        // check if the selected elements are correct, if not reset
        resetSelectedPair();
    }

}

void LetterSalad::resetSelectedPair() {
    _isFirstCellSelected = false;
    _isSecondCellSelected = false;
    if (!LetterSalad::isWordInList(_activeWordList, _selectedWord)) {
        for (auto &lineE : _currentLine) {
            LetterSalad::deSelectBox(lineE);
        }
    } else {
        for (auto &lineE : _currentLine) {
            LetterSalad::finalize(lineE);
            _activeWordList.find(WordTarget{_selectedWord})->setFound();
        }
        bool allWordsFound{true};

        // and check, if the game has ended
        for (auto const &word : _activeWordList) {
            if (!(*word.isFound())) {
                allWordsFound = false;
                break;
            }
        }

        if (allWordsFound) {
            _endboxTitle = "Herzlichen Glückwunsch!";

            int secondsLeft{_timer.getSecondsLeft()};
            std::string minutes{std::to_string(secondsLeft / 60)};
            std::string seconds{std::to_string(secondsLeft % 60)};

            static std::string endboxString =
                "Du hast alle Wörter gefunden!\n"
                "Und sogar noch Zeit übrig gehabt!\n"
                    +minutes+" Minuten und "+seconds+" Sekunden\n";
            _endboxText = endboxString.c_str();
            stop();
        }
    }

    _firstSelectedCell = {-1, -1};
    _secondSelectedCell = {-1, -1};
    _selectedWord = "";
    _currentLine.clear();
}

bool LetterSalad::isWordInList(
    std::set<WordTarget> &wordlist,
    std::string const &word) {
    return wordlist.find(WordTarget{word}) != _activeWordList.end();
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

bool checkIfCoordsAreInRange(Coordinates const &c, int const &min, int const
&max) {
    return c.x >= min && c.y >= min && c.x < max && c.y < max;
}

void LetterSalad::selectBox(Coordinates const &coords) {
    if (checkIfCoordsAreInRange(coords, 0, 20)) {
        _gameField[coords.y][coords.x]->isSelected = true;
    }
}

void LetterSalad::deSelectBox(Coordinates const &coords) {
    if (checkIfCoordsAreInRange(coords, 0, 20)) {
        _gameField[coords.y][coords.x]->isSelected = false;
    }
}

void LetterSalad::finalize(Coordinates const &coords) {
    if (checkIfCoordsAreInRange(coords, 0, 20)) {
        _gameField[coords.y][coords.x]->isSolved = true;
    }
}

void LetterSalad::randomizeGameField() {
    for (auto &row : _gameField) {
        for (auto &box : row) {
            if (box->getLetter() == EMPTY_CELL) {
                std::string letter{std::string(1, 'A'+rand() % 26)};
                box->setLetter(letter);
            }
        }
    }
}

void LetterSalad::getRandomWords() {
    // get random words from another source of words.
    std::vector<WordTarget> randomWords;
    _activeWordList.clear();

    while (_activeWordList.size() < NR_OF_WORDS) {
        int randomIndex{randomInt(0, _wordList.size()-1)};
        auto wordPair{*std::next(_wordList.begin(), randomIndex)};
        _activeWordList.insert(wordPair);
    }
}

void LetterSalad::fillGameFieldWithWordlist() {

    for (const auto &wordPair : _activeWordList) {
        if (!placeWord(wordPair.getWord())) {
            std::cerr << "Could not place word: " << wordPair.getWord()
                      << std::endl;
        }
    }
}

int LetterSalad::randomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool LetterSalad::placeWord(std::string word) {
    // get random orientation // 1 = horizontal, 2 = vertical, 3 = diagonal
    Orientation orientation{randomInt(1, 3)};

    int height{static_cast<int>(_gameField.size())};
    int width{static_cast<int>(_gameField[0].size())};

    bool placed{false};
    int tries{0};

    while (!placed && tries < 1000) {
        tries++;
        int row;
        int col;
        bool reverse{(rand() % 2) != 0};

        switch (orientation) {
            case Orientation::HORIZONTAL: {
                row = randomInt(0, height-word.length());
                col = randomInt(0, width-1);
                if (reverse) std::reverse(word.begin(), word.end());
                break;
            }
            case Orientation::VERTICAL: {
                // place word vertically
                row = randomInt(0, height-1);
                col = randomInt(0, width-word.length());
                break;
            }
            case Orientation::DIAGONAL_DOWN: {
                // place word diagonally top left to bottom right
                row = randomInt(0, height-word.length());
                col = randomInt(0, width-word.length());
                break;
            }
            case Orientation::DIAGONAL_UP: {
                // place word diagonally bottom left to top right
                row = randomInt(word.length()-1, height-1);
                col = randomInt(0, width-word.length());
            }
        }

        bool fits{true};

        for (size_t i{0}; i < word.length(); ++i) {
            int currentRow{row};
            int currentCol{col};
            switch (orientation) {
                case Orientation::HORIZONTAL: {
                    currentCol += i;
                    break;
                }
                case Orientation::VERTICAL: {
                    currentRow += i;
                    break;
                }
                case Orientation::DIAGONAL_DOWN: {
                    currentRow += i;
                    currentCol += i;
                    break;
                }
                case Orientation::DIAGONAL_UP: {
                    currentRow -= i;
                    currentCol += i;
                    break;
                }
            }

            if (currentRow < 0 || currentRow >= height || currentCol < 0
                || currentCol >= width) {
                fits = false;
                break;
            }

            std::string
                letter{_gameField[currentRow][currentCol]->getLetter()};

            if (letter != EMPTY_CELL && letter != std::string(1, word[i])) {
                fits = false;
                break;
            }
        }
        // if the word fits, place it
        if (fits) {
            for (size_t i{0}; i < word.length(); ++i) {
                int currentRow{row};
                int currentCol{col};
                switch (orientation) {
                    case Orientation::HORIZONTAL: {
                        currentCol += i;
                        break;
                    }
                    case Orientation::VERTICAL: {
                        currentRow += i;
                        break;
                    }
                    case Orientation::DIAGONAL_DOWN: {
                        currentRow += i;
                        currentCol += i;
                        break;
                    }
                    case Orientation::DIAGONAL_UP: {
                        currentRow -= i;
                        currentCol += i;
                    }
                    default: {
                        break;
                    }
                }
                _gameField[currentRow][currentCol]
                    ->setLetter(std::string(1, word[i]));
            }
            placed = true;
        } else {
            // try
            if (orientation != Orientation::DIAGONAL_UP && tries % 7 == 0) {
                orientation =
                    Orientation{(rand() % 4)};
            }
        }
    }
    return placed;
}
LetterSalad::LetterSalad()
    : abstract_game::Game(abstract_game::GameID::LETTER_SALAD) {

}

} // namespace game
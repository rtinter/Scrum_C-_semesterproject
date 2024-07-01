#include "LetterSalad.hpp"
#include "Window.hpp"
#include <fstream>
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "imgui_internal.h"
#include "Orientation.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "SceneManager.hpp"
#include "RandomPicker.hpp"
#include "SoundPolice.hpp"
#include <nlohmann/json.hpp>

#define DEBUG false

using json = nlohmann::json;

namespace games {

    LetterSalad::LetterSalad() : abstract_game::Game(abstract_game::GameID::LETTER_SALAD) {
        _gameName = "Buchstaben Salat";
        _gameDescription = "Dieses Spiel testet ob du in der Lage bist, "
                           "über einen längeren Zeitraum, "
                           "konzentriert zu arbeiten.\n"
                           "Gute Augen und die Fähigkeit Muster "
                           "schnell zu erkennen sind wichtig "
                           "für die Berufungen\nPolizei und Feuerwehr.";
        _gameRules = "Du hast 15min Zeit alle versteckten Wörter "
                     "im Buchstabensalat zu finden.";
        _gameControls = "Wörter können vorwärts, rückwärts und "
                        "horizontal, vertikal oder auf beiden diagonalen "
                        "erscheinen.\n\n"
                        "Um ein Wort zu markieren: "
                        "Klicke auf den ersten und letzten "
                        "Buchstaben eines Wortes\n\n"
                        "Die gefundenen Wörter "
                        "werden links in der Liste abgehakt.\n\n";

        loadWordsFromFile();
    }

    std::string LetterSalad::getName() const {
        return _gameName;
    }

    void LetterSalad::stop() {
        _showEndBox = true;
        _isGameRunning = false;
        updateStatistics();
    }

    void LetterSalad::start() {

        if (_wordList.empty()) {
            logger::Logger &logger{logger::Logger::getInstance()};
            logger.log("There are no words in the wordlist. Aborting LetterSalad!", QueueEntryType::SEVERE);
            _showEndBox = true;
            return;
        }

        init();
        fillGameFieldWithRandomWords();

        // When debug mode is enabled, then only print the words.
        // All other fields stay EMPTY_CELL
        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "Simplify"
        if (!DEBUG) {
            randomizeGameField();
        }
        #pragma clang diagnostic pop

        _isGameRunning = true;
        _showStartBox = false;
        _showEndBox = false;
        _timer.start();
    }

    void LetterSalad::reset() {
        _activeWordList.clear();
        _gameField.clear();
        _timer.reset();
        start();
    }

    /**
     * @brief Initializes the game field with empty cells.
     */
    void LetterSalad::init() {
        for (int y{0}; y < 20; y++) {
            std::vector<Box> row;
            for (int x{0}; x < 20; x++) {
                row.emplace_back(EMPTY_CELL);
            }
            _gameField.emplace_back(std::move(row));
        }
    }

    void LetterSalad::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Wörter pro Minute",
                                                                                     _wordsPerMinute);
    }

    // the vector is read in from the file but initialized here
    std::vector<WordTarget> LetterSalad::_wordList;

    void LetterSalad::loadWordsFromFile() {

        // return if the wordlist is not empty
        if (!_wordList.empty()) {
            return;
        }

        logger::Logger &logger{logger::Logger::getInstance()};

        std::fstream file("./config/games/letter_salad_words.json");
        if (!file) {
            logger.log("Error opening or reading the file letter_salad_words.json", QueueEntryType::SEVERE);
            return;
        }

        // cant use uniform initializer :( An exception will be thrown if used.
        json const data = json::parse(file);
        _wordList = {data["wordlist"].begin(), data["wordlist"].end()};
        logger.log("LetterSalad wordlist loaded", QueueEntryType::INFORMATION);

        file.close();
    }

    void LetterSalad::render() {
        ui_elements::InfoBox(
                _gameID,
                _showStartBox,
                "Startbox",
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this] {
                    start();
                }).render();

        if (_isGameRunning) {
            renderGame();
        }

        if (_showEndBox) {
            ui_elements::InfoBox(
                    _gameID,
                    _showEndBox,
                    "Endbox",
                    _endBoxTitle,
                    _endBoxText,
                    [this] {
                        reset();
                    }).render();
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
            timerExpired();
            stop();
        }
    }

    void LetterSalad::renderTextList() {
        if (ImGui::BeginListBox("##textList", ImVec2(350, 900))) {
            for (auto const &wordPair : _activeWordList) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(ImGui::GetStyle().FramePadding.x, 8));
                ImGui::Checkbox(wordPair.getWord().c_str(), wordPair.isFound());
                ImGui::PopStyleVar();
                ImGui::PopItemFlag();
            }

            ImGui::EndListBox(); // ##textList
        }

    }

    void LetterSalad::timerExpired() {
        _endBoxTitle = "Die Zeit ist abgelaufen!";

        int missingWords{0};
        int missingLetters{0};
        // get the number of words that are still missing
        for (auto const &wordTarget : _activeWordList) {
            if (!(*(wordTarget.isFound()))) {
                missingWords++;
                missingLetters += wordTarget.getWord().size();
            }
        }

        std::string missingWord;
        if (missingWords == 1) {
            missingWord = "Wort";
        } else {
            missingWord = "Wörter";
        }

        _wordsPerMinute = (_activeWordList.size() - missingWords) / (TIME_LIMIT / 60.);

        std::string const missingWordsText {"Dir fehlen noch:\n" +
                                              std::to_string(missingWords) + " " + missingWord + "\nBzw. " +
                                              std::to_string(missingLetters) + " Buchstaben."};
        _endBoxText = missingWordsText;
    }

    void LetterSalad::renderGameField() {
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - 360, 50));
        ImGui::BeginChild("##gameField", ImVec2(720, 760));
        ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));

        for (int y = 0; y < _gameField.size(); y++) {
            auto const &row {_gameField[y]};

            for (int x = 0; x < row.size(); x++) {
                // Always print on the same line but the first cell
                if (x > 0) ImGui::SameLine();

                // PushID is used to ensure that each cell has a unique ID
                ImGui::PushID(y * 20 + x);
                if (ImGui::Selectable(
                        _gameField[y][x].getChar(),
                        _gameField[y][x].isSelected || _gameField[y][x].isSolved,
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

                ImGui::PopID();
            }
        }
        ImGui::PopStyleVar();
        ImGui::EndChild(); // ##gameField
    }

    void LetterSalad::renderSelectedWord() const {
        static constexpr int WIDTH {650};
        static constexpr int HEIGHT {40};

        ImVec2 const startPos{ImVec2(ImGui::GetWindowWidth() / 2 - static_cast<int>(WIDTH / 2), 810)};

        ImGui::PushFont(commons::Fonts::_header2);

        ImGui::SetCursorPos(startPos);
        ImGui::BeginChild("##selectedWord", ImVec2(WIDTH, HEIGHT));

        // Get the position and size of the dummy
        ImVec2 const pos {ImGui::GetItemRectMin()};
        ImDrawList *drawList {ImGui::GetWindowDrawList()};
        static constexpr ImU32 RECTANGLE {IM_COL32(3, 161, 252, 255)};
        static constexpr float ROUNDING {25.f};

        drawList->AddRectFilled(pos,
                                ImVec2(pos.x + WIDTH, pos.y + HEIGHT),
                                RECTANGLE,
                                ROUNDING
        );

        ui_elements::TextCentered(_selectedWord.c_str());
        ImGui::PopFont();
        ImGui::EndChild(); // ##selectedWord
    }

    /**
     * @brief When the mouse is hovering over the game field,
     * then draw a straight line between the first selected cell and the hovered cell.
     * Does not hover if no cell has been selected yet.
     *
     * @param coords the coordinates of the hovered cell.
     */
    void LetterSalad::onHover(commons::Coordinates const &coords) {

        static commons::Coordinates lastHoveredCell{-1, -1};

        auto const newlines{getLine(_firstSelectedCell, coords)};

        if (newlines.empty()) {
            return;
        }

        // check if the hovered cell is not the last hovered cell
        if (lastHoveredCell.x != -1 && lastHoveredCell != coords) {
            std::vector<commons::Coordinates> difference;
            // remove all elements that are now not hovered anymore
            std::set_difference(_currentLine.begin(),
                                _currentLine.end(),
                                newlines.begin(),
                                newlines.end(),
                                std::back_inserter(difference));
            for (auto &lineE : difference) {
                deselectBox(lineE);
            }

        } else {
            _selectedWord = "";
            _currentLine = getLine(_firstSelectedCell, coords);

            for (auto const &lineE : _currentLine) {
                selectBox(lineE);
                _selectedWord += _gameField[lineE.y][lineE.x].getChar();
            }
        }

        lastHoveredCell = coords;
    }

    /**
     * @brief When a cell is clicked, check if it is the first or second cell.
     * If the first cell has been clicked, then select it.
     * If the second cell has been clicked, then select it and check if the selected word is correct.
     *
     * @param coords
     */
    void LetterSalad::clickCell(commons::Coordinates const &coords) {
        commons::SoundPolice::safePlaySound(commons::Sound::CLICK, 70);

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
            // check if the selected elements are correct, if not reset
            resetSelectedPair();
        }

    }

    /**
     * @brief Check if the selected word is in the word list.
     * If it is, then finalize the word.
     * If it is not, then deselect the boxes.
     * If all words have been found, then stop the game.
     */
    void LetterSalad::resetSelectedPair() {
        _isFirstCellSelected = false;
        _isSecondCellSelected = false;
        if (!LetterSalad::isWordInList(_activeWordList, _selectedWord)) {
            for (auto const &lineE : _currentLine) {
                LetterSalad::deselectBox(lineE);
            }
        } else {
            for (auto const &lineE : _currentLine) {
                LetterSalad::finalize(lineE);
            }
            auto const foundWord{_activeWordList.find(WordTarget{_selectedWord})};

            if (!(*foundWord->isFound())) {
                foundWord->setFound();
                commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            }

            bool areAllWordsFound{true};

            // and check, if the game has ended
            for (auto const &word : _activeWordList) {
                if (!(*word.isFound())) {
                    areAllWordsFound = false;
                    break;
                }
            }

            if (areAllWordsFound) {
                allWordsFound();
                stop();
            }
        }

        _firstSelectedCell = {-1, -1};
        _selectedWord = "";
        _currentLine.clear();
    }

    void LetterSalad::allWordsFound() {
        _endBoxTitle = "Herzlichen Glückwunsch!";

        int const secondsLeft{_timer.getSecondsLeft()};
        std::string const minutes{std::to_string(secondsLeft / 60)};
        std::string const seconds{std::to_string(secondsLeft % 60)};

        _wordsPerMinute = (_activeWordList.size()) / ((TIME_LIMIT - secondsLeft) / 60.);

        std::string const endboxString {
                "Du hast alle Wörter gefunden!\n"
                "Und sogar noch Zeit übrig gehabt!\n" + minutes +
                " Minuten und " + seconds + " Sekunden\n"};
        _endBoxText = endboxString;

    }

    bool LetterSalad::isWordInList(std::set<WordTarget> &wordlist, std::string const &word) {
        return wordlist.find(WordTarget{word}) != _activeWordList.end();
    }

    /**
     * Get the coordinates of the cells between the start and end cell.
     * Diagonally, horizontally or vertically.
     * Basing on the Bresenham's line algorithm.
     */
    auto LetterSalad::getLine(commons::Coordinates const &start,
                              commons::Coordinates const &end) -> std::vector<commons::Coordinates> {
        std::vector<commons::Coordinates> linePoints;
        int x1{start.x};
        int y1{start.y};
        int x2{end.x};
        int y2{end.y};

        int dx{std::abs(x2 - x1)};
        int sx{x1 < x2 ? 1 : -1};
        int dy{-std::abs(y2 - y1)};
        int sy{y1 < y2 ? 1 : -1};
        int err{dx + dy};
        int e2; // Fehlerwert e_xy

        // make sure to only draw elements
        // if the start and end cell are in one line
        // diagonally or horizontally or vertically
        bool const isDiagonal = {std::abs(dx) == std::abs(dy)};
        bool const isHorizontal = {dy == 0};
        bool const isVertical = {dx == 0};

        // return if the cells are not in one line
        if (!isDiagonal && !isHorizontal && !isVertical) {
            return linePoints;
        }

        while (true) {
            linePoints.emplace_back(y1, x1);
            if (x1 == x2 && y1 == y2) break;
            e2 = 2 * err;
            if (e2 >= dy) { // error is growing in horizontal direction
                err += dy;
                x1 += sx;
            }
            if (e2 <= dx) { // error is growing in vertical direction
                err += dx;
                y1 += sy;
            }
        }
        return linePoints;
    }

    bool checkIfCoordsAreInRange(commons::Coordinates const &c, int const &min, int const &max) {
        return c.x >= min && c.y >= min && c.x < max && c.y < max;
    }

    void LetterSalad::selectBox(commons::Coordinates const &coords) {
        if (checkIfCoordsAreInRange(coords, 0, 20)) {
            _gameField[coords.y][coords.x].isSelected = true;
        }
    }

    void LetterSalad::deselectBox(commons::Coordinates const &coords) {
        if (checkIfCoordsAreInRange(coords, 0, 20)) {
            _gameField[coords.y][coords.x].isSelected = false;
        }
    }

    void LetterSalad::finalize(commons::Coordinates const &coords) {
        if (checkIfCoordsAreInRange(coords, 0, 20)) {
            _gameField[coords.y][coords.x].isSolved = true;
        }
    }

    void LetterSalad::randomizeGameField() {
        for (auto &row : _gameField) {
            for (auto &box : row) {
                if (box.getLetter() == EMPTY_CELL) {
                    std::string const letter{std::string(1, 'A' + rand() % 26)};
                    box.setLetter(letter);
                }
            }
        }
    }

    void LetterSalad::fillGameFieldWithRandomWords() {
        // get random words from another source of words.
        std::vector<WordTarget> randomWords;
        _activeWordList.clear();

        while (_activeWordList.size() < NR_OF_WORDS) {
            int const randomIndex{RandomPicker::randomInt(0, _wordList.size() - 1)};
            auto const wordPair{*std::next(_wordList.begin(), randomIndex)};
            // check if the word can be placed
            if (_activeWordList.find(wordPair) == _activeWordList.end() && placeWord(wordPair.getWord())) {
                // if yes add it to the active wordList
                _activeWordList.insert(wordPair);
            }
        }
    }

    /**
     * @brief Places a word in the game field.
     * Tries 1000 times for a random orientation and position.
     * @param word the word to be placed.
     *
     * @return true if the word could be placed, false otherwise.
     */
    bool LetterSalad::placeWord(std::string word) {
        // get random orientation
        // 0 = horizontal, 1 = vertical, 2 = diagonal_1, 3 = diagonal_2
        Orientation orientation{RandomPicker::randomInt(1, 3)};

        static int const HEIGHT{20};
        static int const WIDTH{20};

        bool placed{false};
        int tries{0};

        while (!placed && tries < 1000) {
            tries++;
            int row;
            int col;
            bool const reverse{(rand() % 2) != 0};

            switch (orientation) {
                case Orientation::HORIZONTAL: {
                    row = RandomPicker::randomInt(0, HEIGHT - word.length());
                    col = RandomPicker::randomInt(0, WIDTH - 1);
                    if (reverse) std::reverse(word.begin(), word.end());
                    break;
                }
                case Orientation::VERTICAL: {
                    // place word vertically
                    row = RandomPicker::randomInt(0, HEIGHT - 1);
                    col = RandomPicker::randomInt(0, WIDTH - word.length());
                    if (reverse) std::reverse(word.begin(), word.end());
                    break;
                }
                case Orientation::DIAGONAL_DOWN: {
                    // place word diagonally top left to bottom right
                    row = RandomPicker::randomInt(0, HEIGHT - word.length());
                    col = RandomPicker::randomInt(0, WIDTH - word.length());
                    if (reverse) std::reverse(word.begin(), word.end());
                    break;
                }
                case Orientation::DIAGONAL_UP: {
                    // place word diagonally bottom left to top right
                    row = RandomPicker::randomInt(word.length() - 1, HEIGHT - 1);
                    col = RandomPicker::randomInt(0, WIDTH - word.length());
                    if (reverse) std::reverse(word.begin(), word.end());
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

                if (currentRow < 0 || currentRow >= HEIGHT || currentCol < 0 || currentCol >= WIDTH) {
                    fits = false;
                    break;
                }

                std::string const letter{_gameField[currentRow][currentCol].getLetter()};

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
                    _gameField[currentRow][currentCol].setLetter(std::string(1, word[i]));
                }
                placed = true;
            } else {
                // try
                if (orientation != Orientation::DIAGONAL_UP && tries % 7 == 0) {
                    orientation = Orientation{(rand() % 4)};
                }
            }
        }
        return placed;
    }

} // namespace game

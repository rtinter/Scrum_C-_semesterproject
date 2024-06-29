#include "RowsOfSymbols.hpp"
#include "InfoBox.hpp"
#include "imgui.h"
#include "Window.hpp"
#include "TextCentered.hpp"
#include "Fonts.hpp"
#include "RandomPicker.hpp"
#include "Symbol.hpp"
#include "Centered.hpp"
#include "Sound.hpp"
#include "SoundPolice.hpp"

namespace game {

    RowsOfSymbols::RowsOfSymbols() : abstract_game::Game(abstract_game::GameID::ROWS_OF_SYMBOLS),
                                    _correctSymbols(0), _wrongSymbols(0), _timer {"Symbolreihen", TOTAL_TIME_SEC} {

        _gameName = "Symbolreihen";

        _gameDescription = "Bei dem Spiel Symbolreihen handelt es sich um einen Test, der die Konzentration auf die Probe stellt.\n"
                           "In einer Linie werden mehrere Symbole angezeigt, die nacheinander an der Reihe sind.\n"
                           "Das aktuelle Symbol auf der linken Seite soll in eine von zwei Kategorien einsortiert werden.\n";

        _gameRules =
                "1. Zur Kategorie 1 gehören alle Symbole mit einem Kreis und drei Punkten\n    oder einem Quadrat und zwei Punkten im Inneren.\n"
                "2. Zur Kategorie 0 gehören alle anderen Symbole.\n"
                "3. Das aktuelle Symbol wird übersprungen, wenn du zu lange brauchst, um dich zu entscheiden.\n"
                "4. Für jede richtige Entscheidung erhältst du einen Punkt,\n    für jede falsche Entscheidung werden dir einige Sekunden abgezogen.\n"
                "5. Das Spiel endet nach 90 Sekunden abzüglich der Zeit, die dir abgezogen wurde.\n";

        _gameControls =
                "Steuerung:\n"
                "1. Unter dem aktuellen Symbol auf der linken Seite befinden sich die beiden Knöpfe, beschriftet mit 1 und 0.\n"
                "2. Klicke auf den Knopf mit der 1, wenn das Symbol im inneren einen Kreis mit drei Punkten\n    oder ein Quadrat mit zwei Punkten darstellt.\n"
                "3. Klicke auf den Knopf mit der 0, für alle Symbole, auf die das nicht zutrifft.\n";
    }

    std::string RowsOfSymbols::getName() const {
        return _gameName;
    }

    void RowsOfSymbols::render() {
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

    void RowsOfSymbols::renderGame() {
        ui_elements::Window("Symbolreihen").render([this]() {

            _timer.render();

            // check if time is up
            if (_timer.isExpiredNow()) {
                stop();
            }

            // check if time is up for current symbol and go to next symbol
            if(isTimeUpForCurrentSymbol()) {
                popCurrentSymbol();
            }

            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered("Symbolreihen");
            ImGui::PopFont();

            updateShownSymbols();
            renderRow();

        });
    }

    void RowsOfSymbols::start() {
        _isGameRunning = true;
        _showStartBox = false;
        _showEndBox = false;
        _symbols.clear();
        _lastSymbolChange = std::chrono::steady_clock::now();
        _timer.start();
    }

    void RowsOfSymbols::reset() {
        _timer.reset();
        _correctSymbols = 0;
        _wrongSymbols = 0;
        start();
    }

    void RowsOfSymbols::stop() {
        _endBoxTitle = "Geschafft!";
        _endBoxText = "Du hast in einer Zeit von " + std::to_string(TOTAL_TIME_SEC) + " Sekunden " + std::to_string(_correctSymbols) + " Symbole richtig erkannt!\n\n"
                     + "In dieser Zeit hast du dich " + std::to_string(_wrongSymbols) + " Mal falsch entschieden und dafür\n"
                     + "eine Zeit von ungefähr " + std::to_string(_wrongSymbols * WRONG_ANSWER_TIME_REDUCTION_SEC) + " Sekunden abgezogen bekommen.";
        _showEndBox = true;
        _isGameRunning = false;
        updateStatistics();
    }

    void RowsOfSymbols::updateStatistics() {

        // add the result of this run through to the current session
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Korrekte Symbole",
                                                                                     _correctSymbols);
    }

    void RowsOfSymbols::updateShownSymbols() {

        while(_symbols.size() < NR_OF_SHOWN_SYMBOLS){

            bool recentlyUsed;
            SymbolType newSymbol;

            // generate new symbol that was not used recently
            do {
                newSymbol = static_cast<SymbolType>(commons::RandomPicker::randomInt(0, 7));

                recentlyUsed = false;
                for(auto &symbol: _lastAddedSymbols) {
                    if (symbol == newSymbol)
                        recentlyUsed = true;
                }

            } while(recentlyUsed);

            // add new symbol to the list of active symbols
            _symbols.push_back(newSymbol);

            // add new symbol to the list of recently used symbols
            _lastAddedSymbols.push_front(_symbols.back());

            // remove the oldest symbol if list (dequeue) is too long
            if(_lastAddedSymbols.size() > NUMBER_OF_RECENTLY_USED_SYMBOLS)
                _lastAddedSymbols.pop_back();
        }
    }

    void RowsOfSymbols::renderRow(){

        ui_elements::Centered(true, false, [this] {

            ImGui::BeginGroup(); // symbols + buttons

            ImGui::BeginGroup(); // symbols

            renderBackgroundRect();

            bool first {true};
            for (auto &symbol: _symbols) {
                Symbol::renderSymbolType(symbol, first);
                first = false;
            }

            ImGui::EndGroup(); // symbols

            renderButtons();

            ImGui::EndGroup(); // symbols + buttons
        });
    }

    void RowsOfSymbols::renderBackgroundRect(){

        // colors for the gradient
        ImU32 colorLeft {IM_COL32(0, 0, 0, 10)};
        ImU32 colorRight {IM_COL32(0, 0, 0, 0)};

        // get the draw list and prepare the total width and gap between the symbols
        ImDrawList &drawList {*ImGui::GetWindowDrawList()};
        int totalWidthOfSymbols {static_cast<int>(SYMBOL_SIZE + MARGIN * 2) * NR_OF_SHOWN_SYMBOLS};
        int totalGapBetweenSymbols {20 * (NR_OF_SHOWN_SYMBOLS - 1)};

        // calculate the top left and bottom right corner of the rectangle
        ImVec2 topLeft {ImGui::GetCursorScreenPos()};
        ImVec2 bottomRight
                {ImVec2(ImGui::GetCursorScreenPos().x + totalWidthOfSymbols + totalGapBetweenSymbols,
                       ImGui::GetCursorScreenPos().y + SYMBOL_SIZE + MARGIN * 2)};

        // draw the gradient background
        drawList.AddRectFilledMultiColor(topLeft, bottomRight,
                                         colorLeft, colorRight,
                                         colorRight, colorLeft);
    }

    void RowsOfSymbols::renderButtons() {
        ImGui::BeginGroup();
        ImGui::PushFont(commons::Fonts::_header2);

        // add the first button with the check if it was clicked
        if (ImGui::Button("1", ImVec2(84, 65)))
            clickButton1();

        // add only a small spacing of 2 pixels between the two buttons
        ImGui::SameLine(0.0f, 2.0f);

        // add the second button with the check if it was clicked
        if (ImGui::Button("0", ImVec2(84, 65)))
            clickButton0();

        ImGui::PopFont();
        ImGui::EndGroup();
    }

    void RowsOfSymbols::clickButton0() {
        SymbolType symbol {_symbols.front()};
        bool correct {false};

        // check if this button 0 is correct for the current symbol
        switch (symbol) {
            case SymbolType::CIRCLE_2_A:
            case SymbolType::CIRCLE_2_B:
            case SymbolType::RECT_3_A:
            case SymbolType::RECT_3_B:
                correct = true;
                break;
            case SymbolType::CIRCLE_3_A:
            case SymbolType::CIRCLE_3_B:
            case SymbolType::RECT_2_A:
            case SymbolType::RECT_2_B:
                correct = false;
                break;
        }

        evaluateAnswer(correct);
    }

    void RowsOfSymbols::clickButton1() {
        SymbolType symbol = _symbols.front();
        bool correct {false};

        // check if this button 1 is correct for the current symbol
        switch (symbol) {
            case SymbolType::CIRCLE_2_A:
            case SymbolType::CIRCLE_2_B:
            case SymbolType::RECT_3_A:
            case SymbolType::RECT_3_B:
                correct = false;
                break;
            case SymbolType::CIRCLE_3_A:
            case SymbolType::CIRCLE_3_B:
            case SymbolType::RECT_2_A:
            case SymbolType::RECT_2_B:
                correct = true;
                break;
        }

        evaluateAnswer(correct);
    }

    void RowsOfSymbols::popCurrentSymbol() {

        // remove the first symbol from the list of shown symbols
        _symbols.pop_front();
        _lastSymbolChange = std::chrono::steady_clock::now();
    }

    void RowsOfSymbols::evaluateAnswer(bool correct) {

        // play sounds and update the correct and wrong symbols counter
        if(correct){
            commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            _correctSymbols++;
        }
        else {
            commons::SoundPolice::safePlaySound(commons::Sound::ERROR);
            _wrongSymbols++;
            _timer.reduceTime(WRONG_ANSWER_TIME_REDUCTION_SEC);
        }

        popCurrentSymbol();
    }

    bool RowsOfSymbols::isTimeUpForCurrentSymbol() const {

        // check if the time for the current symbol is up
        auto timeForSymbolsInMs {std::chrono::milliseconds(static_cast<int>(SYMBOL_TIME_SEC * 1000))};
        return std::chrono::steady_clock::now() - _lastSymbolChange > timeForSymbolsInMs;
    }
}
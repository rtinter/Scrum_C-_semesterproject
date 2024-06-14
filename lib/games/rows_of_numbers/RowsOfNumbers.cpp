//
// Created by jane on 14.06.24.
//

#include "RowsOfNumbers.hpp"
#include <InfoBox.hpp>
#include <Window.hpp>
#include <Fonts.hpp>
#include <TextCentered.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace game {
    RowsOfNumbers::RowsOfNumbers() : abstract_game::Game(abstract_game::GameID::ROWS_OF_NUMBERS) {
        _gameName = "Zahlenreihen";
        _gameDescription = "Finde die fehlende Zahl in der Zahlenreihe.";
        _gameRules = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";
        _gameControls = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";

        loadWordsFromFile();
    }

    // the vector is read in from the file
    std::vector<WordTarget> RowsOfNumbers::_wordList;

    void RowsOfNumbers::loadWordsFromFile() {
        std::fstream file("./config/games/rows_of_numbers.json");
        if (!file) {
            std::cerr << "Unable to open file letter_salad_words.json";
            return;
        }

        json data = json::parse(file);
        _wordList = {data["sequences"].begin(), data["sequences"].end()};

        file.close();
    }

    void RowsOfNumbers::render() {
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

        ui_elements::InfoBox(
                _gameID,
                _showEndBox,
                "Endbox",
                _endBoxTitle,
                _endBoxText,
                [this] {
                    reset();
                }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void RowsOfNumbers::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);

        ui_elements::Window("Zahlenreihen").render([]() {

            ImGui::Spacing();

            ImGui::PushFont(commons::Fonts::_header1);
            //ui_elements::TextCentered(_wordList[0].getWord().c_str());
            ImGui::PopFont();

            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered("Füge die fehlende Zahl ein:");
            ImGui::PopFont();
        });

        ImGui::PopStyleColor();
    }

    void RowsOfNumbers::start() {
        _isGameRunning = true;
        _showEndBox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void RowsOfNumbers::reset() {

    }

    void RowsOfNumbers::updateStatistics() {

    }

    void RowsOfNumbers::stop() {
        _isGameRunning = false;
    }

    std::string RowsOfNumbers::getName() const {
        return Game::getName();
    }

    RowsOfNumbers::~RowsOfNumbers() {

    }


} // game
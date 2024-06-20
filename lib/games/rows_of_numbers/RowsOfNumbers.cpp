
#include "RowsOfNumbers.hpp"
#include "Sequence.hpp"
#include <InfoBox.hpp>
#include <Window.hpp>
#include <Fonts.hpp>
#include <TextCentered.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <random>

using json = nlohmann::json;

namespace game {
    RowsOfNumbers::RowsOfNumbers() : abstract_game::Game(abstract_game::GameID::ROWS_OF_NUMBERS) {
        _gameName = "Zahlenreihen";
        _gameDescription = "Finde die fehlende Zahl in der Zahlenreihe.";
        _gameRules = "1. Analysiere die gezeigte Zahlenreihe.\n2. Finde die fehlende Zahl.\n3. Tippe die fehlende Zahl in das Eingabefeld.\n4. Bestätige die Eingabe durch Enter.";
        _gameControls = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";

        loadWordsFromFile();
    }

    // the vector is read in from the file
    std::vector<game::Sequence> RowsOfNumbers::_sequences;

    void RowsOfNumbers::loadWordsFromFile() {
        try {
            std::fstream file("./config/games/rows_of_numbers.json");
            if (!file) {
                std::cerr << "Unable to open file letter_salad_words.json";
                return;
            }

            json data = json::parse(file);
            _sequences = {data["sequences"].begin(), data["sequences"].end()};

            file.close();
        } catch (const std::exception &e) {
            std::cerr << "Error while reading file: " << e.what() << std::endl;
        }
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

        ui_elements::Window("Zahlenreihen").render([this]() {
                ImGui::Spacing();

                ImGui::PushFont(commons::Fonts::_header1);

                auto now{std::chrono::steady_clock::now()};
                auto timeSinceCorrectAnswer{
                        std::chrono::duration_cast<std::chrono::seconds>(now - _correctAnswerTime).count()};


            if (_inputChanged && _input == _currentSolution) {
                    _correctAnswerTime = std::chrono::steady_clock::now();
                    _waitingForNextNumber = true;
                } else if (_inputChanged && _input != _currentSolution) {
                    ui_elements::TextCentered("Falsch!");
                    _showEndBox = true;
                    if (_solvedCounter > (_sequences.size() / 2)){
                        _endBoxTitle = "Gut gemacht!";
                    }
                    else{
                        _endBoxTitle = "Probiere es nochmal!";
                    }
                    _endBoxText = "Du hast " + std::to_string(_solvedCounter) + " von " + std::to_string(_sequences.size()) + " Zahlenreihen gelöst.\n\n" +
                            + "Die Lösung der letzten Aufgabe: " + std::to_string(_currentSolution) + "\n" + _currentExplanation;
                }

                if (_waitingForNextNumber && timeSinceCorrectAnswer >= 1) { // Warten Sie 5 Sekunden, bevor Sie die nächste Zahl generieren
                    _randomSequence = randomIndexGenerator(_sequences.size());
                    _currentSequence = _sequences[_randomSequence].sequence;
                    _currentSolution = _sequences[_randomSequence].solution;
                    _currentExplanation = _sequences[_randomSequence].explanation;
                    _waitingForNextNumber = false;
                    _solvedCounter++;
                    _inputChanged = false;
                    _input = 0;
                }

                if (!_waitingForNextNumber && timeSinceCorrectAnswer < 1) { // Display "Richtig!" for 5 seconds
                    ui_elements::TextCentered("Richtig!");
                }

                ui_elements::TextCentered(_currentSequence.c_str());
                ImGui::PopFont();

                ImGui::Spacing();

                ImGui::PushFont(commons::Fonts::_header2);
                ui_elements::TextCentered("Füge die fehlende Zahl ein:");
                ImGui::SameLine();
                ImGui::PushItemWidth(100);
                if (ImGui::InputInt("##input", &_input, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    _inputChanged = true;
                }
                ImGui::PopItemWidth();
                ImGui::PopFont();
        });

        ImGui::PopStyleColor();
    }

    void RowsOfNumbers::start() {
        _inputChanged = false;
        _input = 0;
        _solvedCounter = 0;
        _randomSequence = randomIndexGenerator(_sequences.size());
        _currentSequence = _sequences[_randomSequence].sequence;
        _currentSolution = _sequences[_randomSequence].solution;
        _currentExplanation = _sequences[_randomSequence].explanation;
        _isGameRunning = true;
        _showEndBox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void RowsOfNumbers::reset() {
        start();
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
        _input = 0;
        _solvedCounter = 0;
    }

    int RowsOfNumbers::randomIndexGenerator(int size) const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size - 1);
        return dis(gen);
    }


} // game
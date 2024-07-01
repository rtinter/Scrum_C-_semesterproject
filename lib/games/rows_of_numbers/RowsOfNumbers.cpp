
#include "RowsOfNumbers.hpp"
#include "Sequence.hpp"
#include <InfoBox.hpp>
#include <Window.hpp>
#include <Fonts.hpp>
#include <TextCentered.hpp>
#include <RandomPicker.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <random>
#include <SoundPolice.hpp>

using json = nlohmann::json;

namespace games {
    RowsOfNumbers::RowsOfNumbers() : Game(abstract_game::GameID::ROWS_OF_NUMBERS) {
        _gameName = "Zahlenreihen";
        _gameDescription = "Finde die fehlende Zahl in der Zahlenreihe.";
        _gameRules = "1. Analysiere die gezeigte Zahlenreihe.\n2. Finde die fehlende Zahl.\n3. Tippe die fehlende Zahl in das Eingabefeld.\n4. Bestätige die Eingabe durch Enter.";
        _gameControls = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";

        loadWordsFromFile();
    }

    // the vector is read in from the file
    std::vector<Sequence> RowsOfNumbers::_sequences;

    /*********************************
    *  Loads the words from the configuration file and stores them in _sequences.
    ***********************************/
    void RowsOfNumbers::loadWordsFromFile() {
        try {
            std::fstream file("./config/games/rows_of_numbers.json");
            if (!file) {
                std::cerr << "Unable to open file letter_salad_words.json";
                return;
            }

            // Cant use {} for initialization due to runtime error
            json const data = json::parse(file);
            _sequences = {data["sequences"].begin(), data["sequences"].end()};

            file.close();
        } catch (std::exception const &e) {
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

        ui_elements::Window(_gameName).render([this] {
            ImGui::Spacing();

            ImGui::PushFont(commons::Fonts::_header1);

            _now = std::chrono::steady_clock::now();
            _timeSinceCorrectAnswer =
                    std::chrono::duration_cast<std::chrono::seconds>(_now - _correctAnswerTime).count();

            // if the input is changed as well as correct we wait for the next row of numbers
            // if the input is changed and not correct we show the end box with the explanation
            if (_inputChanged && _input == _currentSolution) {
                _correctAnswerTime = std::chrono::steady_clock::now();
                _waitingForNextNumber = true;
                commons::SoundPolice::safePlaySound(Sound::CORRECT);
            } else if (_inputChanged && _input != _currentSolution) {
                ui_elements::TextCentered("Falsch!");
                commons::SoundPolice::safePlaySound(Sound::ERROR);
                if (_solvedCounter > (_sequences.size() / 2))
                    _endBoxTitle = "Gut gemacht!";
                else
                    _endBoxTitle = "Probiere es nochmal!";
                _endBoxText =
                        "Du hast " + std::to_string(_solvedCounter) + " von " + std::to_string(_sequences.size()) +
                        " Zahlenreihen gelöst.\n\n" +
                        +"Die Lösung der letzten Aufgabe: " + std::to_string(_currentSolution) + "\n" +
                        _currentExplanation;
                stop();
            }

            // Wait 5 seconds before showing the next number
            if (_waitingForNextNumber &&
                _timeSinceCorrectAnswer >= 1) {
                _randomSequence = commons::RandomPicker::randomInt(0,_sequences.size());
                _currentSequence = _sequences[_randomSequence].sequence;
                _currentSolution = _sequences[_randomSequence].solution;
                _currentExplanation = _sequences[_randomSequence].explanation;
                _waitingForNextNumber = false;
                _solvedCounter++;
                _inputChanged = false;
                _input = 0;
            }

            // Display "Richtig!" for 5 seconds
            if (!_waitingForNextNumber && _timeSinceCorrectAnswer < 1) {
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
        _randomSequence = commons::RandomPicker::randomInt(0,_sequences.size());
        _currentSequence = _sequences[_randomSequence].sequence;
        _currentSolution = _sequences[_randomSequence].solution;
        _currentExplanation = _sequences[_randomSequence].explanation;

        _isGameRunning = true;
        _showEndBox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void RowsOfNumbers::reset() {
        // reset the game
        _currentSequence.clear();
        _currentExplanation.clear();
        start();
    }

    void RowsOfNumbers::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten",
                                                                                     _solvedCounter);
    }

    void RowsOfNumbers::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;

        _waitingForNextNumber = false;
        _inputChanged = false;
    }

    std::string RowsOfNumbers::getName() const {
        return _gameName;
    }

    RowsOfNumbers::~RowsOfNumbers() {
        _input = 0;
        _solvedCounter = 0;
    }


} // game

#include "Calc.hpp"
#include "Overlay.hpp"
#include "InfoBox.hpp"
#include "../commons/Fonts.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "Window.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <sstream>

namespace games {
    Calc::Calc()
            : _currentTask(0, {{0, '+'}}), _taskTimer("Schnelles Rechnen", 30), _displayTimer("Schnelles Rechnen", 4), _state(SHOW_START_NUMBER) {
        _gameName = "Schnelles Rechnen";
        _gameDescription = "Unser Spiel 'Schnelles Rechnen' testet die Merkfähigkeit und Kopfrechenfähigkeit, "
                           "die für Polizei- und Feuerwehranwärter unerlässlich sind. Durch die schnelle Abfolge "
                           "von Rechenoperationen und die anschließende Berechnung des Ergebnisses im Kopf wird die "
                           "Fähigkeit zur schnellen, genauen mentalen Verarbeitung gefordert.";
        _gameRules = "Es werden Rechenaufgaben angezeigt, die im Kopf gelöst werden müssen. Die Schwierigkeit erhöht sich mit jeder Runde.";
        _gameControls = "Eingabefeld: Ergebnis der Rechenaufgabe eingeben und bestätigen.";

        // Generate the initial task after the TaskGenerator is constructed
        _currentTask = _taskGenerator.generateTask(_currentLevel, _currentResult);
    }

    void Calc::start() {
        reset();
        _isGameRunning = true;
        _showInfobox = false;
        _taskTimer.start();
        _displayTimer.start();  // Start the display timer with 4 seconds
    }

    void Calc::reset() {
        _currentTask = _taskGenerator.generateTask(_currentLevel, 0);
        _numberOfCorrectAnswers = 0;
        _currentScore = 0;
        _showInfobox = true;
        _state = SHOW_START_NUMBER;
    }

    void Calc::render() {
        if (_showInfobox) {
            ui_elements::InfoBox(_showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
                start();
            }).render();
        } else if (_isGameRunning) {
            renderGame();
        }
    }

    void Calc::renderGame() {
        ui_elements::Window("Schnelles Rechnen").render([this] {
            _taskTimer.render();
            _displayTimer.render();

            if (_taskTimer.isExpiredNow()) {
                stop();
            } else {
                switch (_state) {
                    case SHOW_START_NUMBER:
                        ImGui::Text("Startwert: %d", _currentTask.getCurrentResult());
                        _state = SHOW_OPERATION;
                        _displayTimer.start(); // Restart the display timer for 4 seconds
                        break;

                    case SHOW_OPERATION:
                        displayTask();
                        if (_displayTimer.isExpiredNow()) {
                            if (_currentTask.hasMoreOperations()) {
                                _currentTask.advance();
                                _displayTimer.start(); // Restart the display timer for the next operation
                            } else {
                                _state = WAIT_FOR_INPUT;
                            }
                        }
                        break;

                    case WAIT_FOR_INPUT:
                        ImGui::Text("Geben Sie das Endergebnis ein:");
                        static char input[128] = "";
                        ImGui::InputText("##input", input, sizeof(input));
                        if (ImGui::Button("Bestätigen")) {
                            int playerAnswer = std::atoi(input);
                            checkAnswer(playerAnswer);
                            std::fill(std::begin(input), std::end(input), 0);  // Clear input
                        }
                        break;
                }
            }
        });
    }

    void Calc::stop() {
        _isGameRunning = false;
        _showEndbox = true;
        _endboxTitle = "Zeit abgelaufen!";
        std::string endboxText = "Richtige: " + std::to_string(_numberOfCorrectAnswers) + "\nLängster Streak: " + std::to_string(_numberOfCorrectAnswers);
        _endboxText = endboxText.c_str();  // Hier wird die Zeichenkette korrekt zugewiesen
    }

    void Calc::updateStatistics() {
        // Statistik-Update-Logik hier
    }

    void Calc::displayTask() {
        if (_currentTask.hasMoreOperations()) {
            ImGui::Text("Berechnung: %c %d", _currentTask.getCurrentOperator(), _currentTask.getCurrentNumber());
        } else {
            ImGui::Text("Keine weiteren Aufgaben.");
        }
    }

    void Calc::checkAnswer(int playerAnswer) {
        if (_currentTask.getCurrentResult() == playerAnswer) {
            _numberOfCorrectAnswers++;
            _currentScore++;
            // Grünes Feedback
            ImGui::Text("Richtige Antwort!");

            // Gehe zur nächsten Aufgabe, falls vorhanden
            if (_currentTask.hasMoreOperations()) {
                _currentTask.advance();
            } else {
                // Level abgeschlossen
                _endboxTitle = "Level abgeschlossen";
                _endboxText = "Level erfolgreich abgeschlossen! Möchten Sie zum nächsten Level wechseln?";
                _showEndbox = true;
                _isGameRunning = false;
            }
        } else {
            // Rotes Feedback
            ImGui::Text("Falsche Antwort!");
            _isGameRunning = false;
            _showEndbox = true;
            _endboxTitle = "Spiel beendet";
            _endboxText = "Falsche Antwort. Spiel beendet.";
        }
    }
}

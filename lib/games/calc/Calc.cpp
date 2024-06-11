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
#include <sstream>
#include <thread>

namespace games {
    Calc::Calc()
            : _currentTask(std::vector<std::pair<int, char>>{}) {  // Initialisierung des _currentTask mit einem leeren Vektor
        _gameName = "Schnelles Rechnen";
        _gameDescription = "Unser Spiel 'Schnelles Rechnen' testet die Merkfähigkeit und Kopfrechenfähigkeit, "
                           "die für Polizei- und Feuerwehranwärter unerlässlich sind. Durch die schnelle Abfolge "
                           "von Rechenoperationen und die anschließende Berechnung des Ergebnisses im Kopf wird die "
                           "Fähigkeit zur schnellen, genauen mentalen Verarbeitung gefordert.";
        _gameRules = "Es werden Rechenaufgaben angezeigt, die im Kopf gelöst werden müssen. Die Schwierigkeit erhöht sich mit jeder Runde.";
        _gameControls = "Eingabefeld: Ergebnis der Rechenaufgabe eingeben und bestätigen.";
    }

    void Calc::start() {
        reset();
        _isGameRunning = true;
        _showInfobox = false;
        generateTask();
    }

    void Calc::reset() {
        _numberOfCorrectAnswers = 0;
        _currentScore = 0;
        _currentResult = 0;
        _displayDuration = std::chrono::seconds(2);
        _showInfobox = true;
    }

    void Calc::render() {
        if (_showInfobox) {
            ui_elements::InfoBox(_showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
                start();
            }).render();
        } else if (_isGameRunning) {
            //renderGame();
        }
    }

    void Calc::renderGame() {
        ui_elements::Window("Schnelles Rechnen").render([this] {
            _taskTimer.render();

            if (_taskTimer.isExpiredNow()) {
                stop();
            }

            displayTask();

            static char input[128] = "";
            ImGui::InputText("##input", input, sizeof(input));
            if (ImGui::Button("Bestätigen")) {
                int playerAnswer = std::atoi(input);
                checkAnswer(playerAnswer);
                std::fill(std::begin(input), std::end(input), 0);  // Clear input
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

    void Calc::generateTask() {
        _currentTask = _taskGenerator.generateTask(_currentLevel, _currentResult);
    }

    void Calc::displayTask() {
        if (_currentTask.hasMoreOperations()) {
            std::string operation = std::string(1, _currentTask.getCurrentOperator()) + " " + std::to_string(_currentTask.getCurrentNumber());
            ImGui::Text("%s", operation.c_str());
            std::this_thread::sleep_for(_displayDuration);
            _displayDuration = std::max(std::chrono::seconds(1), _displayDuration - std::chrono::seconds(1));
            _currentTask.advance();
        } else {
            ImGui::Text("Geben Sie das Ergebnis ein:");
        }
    }

    void Calc::checkAnswer(int playerAnswer) {
        if (playerAnswer == _currentTask.getCurrentResult()) {
            _numberOfCorrectAnswers++;
            _currentScore++;
            // Grünes Feedback
            ImGui::Text("Richtige Antwort!");
        } else {
            // Rotes Feedback
            ImGui::Text("Falsche Antwort!");
        }

        if (_numberOfCorrectAnswers == _numberOfTasks) {
            _endboxTitle = "Level abgeschlossen";
            _endboxText = "Level erfolgreich abgeschlossen! Möchten Sie zum nächsten Level wechseln?";
            _showEndbox = true;
        } else {
            _endboxTitle = "Spiel beendet";
            _endboxText = "Falsche Antwort. Spiel beendet.";
            _showEndbox = true;
            _isGameRunning = false;
        }
    }
}

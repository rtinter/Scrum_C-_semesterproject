#include "Calc.hpp"
#include "Overlay.hpp"
#include "../commons/Fonts.hpp"
#include "TextCentered.hpp"
#include "InfoBox.hpp"
#include "Centered.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "MathTaskFactory.hpp"
#include "Window.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include "MathTaskType.hpp"

namespace games {
    Calc::Calc() : abstract_game::Game(abstract_game::GameID::CALC), _timer("Schnelles Rechnen", 10) { // Initialize the timer with 10 seconds and the window name
        _gameName = "Schnelles Rechnen";
        _gameDescription = "Unser Spiel 'Schnelles Rechnen' testet die Merkfähigkeit und Kopfrechenfähigkeit,\n"
                           "die für Polizei- und Feuerwehranwärter unerlässlich sind. Durch die schnelle Abfolge\n"
                           "von Rechenoperationen und die anschließende Berechnung des Ergebnisses im Kopf wird\n"
                           "die Fähigkeit zur schnellen, genauen mentalen Verarbeitung gefordert.";
        _gameRules = "Es werden Rechenaufgaben angezeigt, die im Kopf gelöst werden müssen.\n"
                     "Die Schwierigkeit erhöht sich mit jeder Runde.";
        _gameControls = "Eingabefeld: Ergebnis der Rechenaufgabe eingeben und bestätigen.";
        _endScreenTitle = "Spiel beendet";
        _endScreenStatisticText = "";
        _averageTimeText = ""; // Initialize the new member variable
    }

    void Calc::start() {
        _completedLevels = 0;
        _showEndbox = false;
        _endTime.reset();
        _startTime = std::chrono::steady_clock::now();
        _timerSeconds = 7; // Reset the timer to 10 seconds at the start
        nextLevel(_difficulty_level);
    }

    void Calc::nextLevel(int difficulty_level) {
        _currentLevel = math_task_factory::createRandomMathTask(1);
        _currentLevel->start();
        _timer.resetWithNewTime(_timerSeconds);  // Reset the timer with current timerSeconds
        _timer.start();  // Start the timer
    }

    void Calc::renderGame() {
        ui_elements::Window("Schnelles Rechnen").render([this] {
            _timer.render(); // Render the timer
            _currentLevel->render(); // Render the current level
        });
    }

    void Calc::render() {
        ui_elements::InfoBox(
                _gameID, _showInfobox, "Startbox",
                _gameName, _gameDescription, _gameRules, _gameControls,
                [this]() { start(); }
        ).render();

        if (_showInfobox) {
            return;
        }

        if (_timer.isExpiredNow()) {
            _endTime = std::chrono::steady_clock::now();
            calculateEndScreenText();
            _showEndbox = true;
            stop();
        }

        if (!_currentLevel->isRunning()) {
            if (!_currentLevel->wasSuccessfullyCompleted()) {
                // Make sure to only capture endtime once per game
                if (!_endTime.has_value()) {
                    _endTime = std::chrono::steady_clock::now();
                    calculateEndScreenText();
                }
                _showEndbox = true;
            } else {
                _completedLevels++;

                // Decrease timer by 1 second for each level increase, but not below 2 seconds
                if (_completedLevels % 4 == 0) {
                    _difficulty_level++;
                    _timerSeconds = std::max(2, _timerSeconds - 1);
                }

                nextLevel(_difficulty_level);
            }
        }

        if (_showEndbox) {
            showEndScreen();
            return;
        }

        renderGame(); // Render the game and the timer
    }

    void Calc::showEndScreen() {
        _showEndbox = true;
        ui_elements::Overlay("EndScreen", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(_endScreenTitle.c_str());
            ImGui::PopFont();

            std::istringstream endScreenTextStream(_endScreenStatisticText);
            std::string line;
            while (std::getline(endScreenTextStream, line)) {
                ui_elements::TextCentered(line.c_str());
            }

            // Render the average time text separately
            ui_elements::TextCentered(_averageTimeText.c_str());

            ui_elements::Centered(true, true, [this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    start();
                }

                if (ImGui::Button("Zurück zur Startseite")) {
                    scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                }
            });
        });
    }

    void Calc::calculateEndScreenText() {
        _elapsedTimeCalculated = getElapsedTimeInSeconds();

        std::ostringstream endScreenTextStream;
        endScreenTextStream << "Du hast insgesamt " << _completedLevels << " Aufgaben erfolgreich gelößt.";
        _endScreenStatisticText = endScreenTextStream.str();

        if (_completedLevels > 0) {
            double averageTimePerTask = _elapsedTimeCalculated / _completedLevels;
            std::ostringstream averageTimeStream;
            averageTimeStream << "Durchschnittlich hast du " << std::round(averageTimePerTask) << " Sekunden für eine Aufgabe gebraucht.";
            _averageTimeText = averageTimeStream.str();
        } else {
            _averageTimeText = "Keine Aufgaben erfolgreich gelöst.";
        }
    }

    std::string Calc::getName() const {
        return "Schnelles Rechnen";
    }

    void Calc::reset() {}

    void Calc::stop() {
        updateStatistics();
    }

    double Calc::getElapsedTimeInSeconds() const {
        if (!_endTime.has_value()) {
            return 0.0;
        }
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(*_endTime - _startTime.value());
        return static_cast<double>(duration.count());
    }

    void Calc::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten",
                                                                                     _completedLevels);
    }
}

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
#include <cmath>

namespace games {
    Calc::Calc() : abstract_game::Game(abstract_game::GameID::CALC) {
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
    }

    void Calc::start() {
        _completedLevels = 0;
        _showEndbox = false;
        _endTime.reset();
        _startTime = std::chrono::steady_clock::now();
        nextLevel();
    }

    void Calc::nextLevel() {
        _currentLevel = math_task_factory::createRandomMathTask();
        _currentLevel->start();
    }

    void Calc::renderGame() {
        ui_elements::Window("Schnelles Rechnen").render([this] {
            _currentLevel->render();
        });
    }

    void Calc::render() {
        ui_elements::InfoBox(_gameID, _showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this]() {
            start();
        }).render();

        if (_showInfobox)
            return;

        if (!_currentLevel->isRunning()) {
            if (!_currentLevel->wasSuccessfullyCompleted()) {
                if (!_endTime.has_value()) {
                    _endTime = std::chrono::steady_clock::now();
                    calculateEndScreenText();
                }
                _showEndbox = true;
            } else {
                _completedLevels++;
                nextLevel();
            }
        }

        if (_showEndbox) {
            showEndScreen();
        } else {
            renderGame();
        }
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
        endScreenTextStream << "Richtig gelöste Aufgaben: " << _completedLevels << "\n";

        if (_completedLevels > 0) {
            double averageTimePerTask = _elapsedTimeCalculated / _completedLevels;
            endScreenTextStream << "Durchschnittlich benötigte Zeit pro Aufgabe: " << std::round(averageTimePerTask) << " Sekunden";
        } else {
            endScreenTextStream << "Keine Aufgaben erfolgreich gelöst.";
        }

        _endScreenStatisticText = endScreenTextStream.str();
    }

    std::string Calc::getName() const {
        return "Schnelles Rechnen";
    }

    void Calc::reset() {}

    void Calc::stop() {}

    double Calc::getElapsedTimeInMinutes() const {
        if (!_endTime.has_value()) {
            return 0.0;
        }
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(*_endTime - _startTime);
        return duration.count() / 60.0;
    }

    double Calc::getElapsedTimeInSeconds() const {
        if (!_endTime.has_value()) {
            return 0.0;
        }
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(*_endTime - _startTime);
        return static_cast<double>(duration.count());
    }

    void Calc::updateStatistics() {
        // Add logic for updating statistics here if needed
    }
}

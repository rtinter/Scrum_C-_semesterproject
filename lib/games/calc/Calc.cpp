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
    Calc::Calc() :
    abstract_game::Game(abstract_game::GameID::CALC),
    _timer("Schnelles Rechnen", 10),
    _difficulty_level(1),
    _completedLevels(1),
    _showEndbox(false),
    _showInfobox(true),
    _elapsedTimeCalculated(0.0),
    _timerSeconds(7)
    {
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
        _averageTimeText = "";
    }

    void Calc::start() {
        _completedLevels = 0;
        _showEndbox = false;
        _endTime.reset();
        _startTime = std::chrono::steady_clock::now();

        // Initial time available to solve the first 4 tasks
        _timerSeconds = 7;
        nextLevel();
    }

    void Calc::nextLevel() {
        _currentLevel = math_task_factory::createRandomMathTask();
        _currentLevel->start();

        // Reset the timer with current timerSeconds
        _timer.resetWithNewTime(_timerSeconds);
        _timer.start();
    }

    void Calc::renderGame() {
        ui_elements::Window("Schnelles Rechnen").render([this] {
            _timer.render();
            _currentLevel->render();
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
                    stop();
                }
                _showEndbox = true;
            } else {
                _completedLevels++;

                // Decrease timer by 1 second for each level increase, but not below 2 seconds to keep the game fair :)
                if (_completedLevels % 4 == 0) {
                    _difficulty_level++;
                    _timerSeconds = std::max(2, _timerSeconds - 1);
                }

                nextLevel();
            }
        }

        if (_showEndbox) {
            showEndScreen();
            return;
        }

        renderGame();
    }

    void Calc::showEndScreen() {
        _showEndbox = true;
        std::ostringstream endScreenTextStream;
        endScreenTextStream << _endScreenStatisticText << "\n\n"
                            << _averageTimeText;
        std::string endScreenText {endScreenTextStream.str()};

        ui_elements::InfoBox(
                _gameID, _showEndbox, "Endbox",
                _endScreenTitle, endScreenText,
                [this]() { start(); }
        ).render();
    }

    void Calc::calculateEndScreenText() {
        _elapsedTimeCalculated = getElapsedTimeInSeconds();

        std::ostringstream endScreenTextStream;
        endScreenTextStream << "Du hast insgesamt " << _completedLevels << " Aufgaben erfolgreich gelöst.";
        _endScreenStatisticText = endScreenTextStream.str();

        if (_completedLevels > 0) {
            double averageTimePerTask {_elapsedTimeCalculated / _completedLevels};
            std::ostringstream averageTimeStream;
            averageTimeStream << "Durchschnittlich hast du " << std::round(averageTimePerTask)
                              << " Sekunden für eine Aufgabe gebraucht.";
            _averageTimeText = averageTimeStream.str();
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
        auto duration {std::chrono::duration_cast<std::chrono::seconds>(*_endTime - _startTime.value())};
        return static_cast<double>(duration.count());
    }

    void Calc::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten",
                                                                                     _completedLevels);
    }
}

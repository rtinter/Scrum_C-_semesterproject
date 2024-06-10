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
#include <thread>

namespace games {
    Calc::Calc() {
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
        render();
    }

    void Calc::reset() {
        _currentTasks.clear();
        _numberOfCorrectAnswers = 0;
        _currentScore = 0;
        _currentLevel = 1;
        _displayDuration = std::chrono::seconds(2);
        _showInfobox = true;
    }

    void Calc::render() {
        if (_showInfobox) {
            ui_elements::Overlay("Spielstart", _showInfobox).render([this]() {
                ImGui::PushFont(commons::Fonts::_header2);
                ui_elements::TextCentered(std::move(_gameName));
                ImGui::PopFont();
                ImGui::TextWrapped(_gameDescription);
                ImGui::TextWrapped(_gameRules);
                ImGui::TextWrapped(_gameControls);

                ui_elements::Centered([this]() {
                    if (ImGui::Button("Ein neues Spiel starten")) {
                        _showInfobox = false;
                        start();
                    }

                    if (ImGui::Button("Hauptmenü")) {
                        scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                    }
                });
            });
        } else if (_isGameRunning) {
            renderGame();
        }
    }

    void Calc::renderGame() {
    }

    void Calc::stop() {
    }

    void Calc::updateStatistics() {
    }

    void Calc::generateTasks() {
    }

    void Calc::displayTasks() {
    }

    int Calc::calculateResult(const std::string &task) {
        return 0;
    }
}

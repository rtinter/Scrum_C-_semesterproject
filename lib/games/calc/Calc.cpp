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

namespace games {
    Calc::Calc() : abstract_game::Game(abstract_game::GameID::CALC){
        _gameName = "Schnelles Rechnen";
        _gameDescription = "Unser Spiel 'Schnelles Rechnen' testet die Merkfähigkeit und Kopfrechenfähigkeit, "
                           "die für Polizei- und Feuerwehranwärter unerlässlich sind. Durch die schnelle Abfolge "
                           "von Rechenoperationen und die anschließende Berechnung des Ergebnisses im Kopf wird die "
                           "Fähigkeit zur schnellen, genauen mentalen Verarbeitung gefordert.";
        _gameRules = "Es werden Rechenaufgaben angezeigt, die im Kopf gelöst werden müssen. Die Schwierigkeit erhöht sich mit jeder Runde.";
        _gameControls = "Eingabefeld: Ergebnis der Rechenaufgabe eingeben und bestätigen.";
    }

    void Calc::start() {
        _completedLevels = 0;
        _showEndbox = false;
        nextLevel();
    }

    void Calc::nextLevel() {
        _currentLevel = math_task_factory::createRandomMathTask();
        _currentLevel->start();
    }

    void Calc::render() {
        ui_elements::InfoBox(_gameID, _showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this]() {
            start();
        }).render();

        if (_showInfobox)
            return;

        if (!_currentLevel->isRunning()) {

            if (!_currentLevel->wasSuccessfullyCompleted()) {
                showEndScreen();
                return;
            }

            _completedLevels++;
            nextLevel();
        }

        _currentLevel->render();
    }

    void Calc::showEndScreen() {
        _showEndbox = true;
        ui_elements::Overlay("EndScreen", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endScreenTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endScreenText));

            ui_elements::Centered(true, true,[this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    start();
                }

                if (ImGui::Button("Zurück zur Startseite")) {
                    scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                }
            });
        });
    }

    std::string Calc::getName() const {
        return "Schnelles Rechnen";
    }

    void Calc::renderGame() {

    }

    void Calc::reset() {

    }

    void Calc::stop() {
        Game::stop();
    }

    void Calc::updateStatistics() {

    }
}
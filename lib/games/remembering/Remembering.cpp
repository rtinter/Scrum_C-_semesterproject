#pragma once

#include "Remembering.hpp"
#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>


namespace games {

    Remembering::Remembering() {
        _gameName = "Remembering";
        _gameDescription =
                "Unser Merkspiel bewertet die Fähigkeit, sich schnell und präzise Fakten zu merken,\n"
                "was für Polizei- und Feuerwehrarbeit unerlässlich ist.\n"
                "In diesen Berufen ist es entscheidend, rasch und genau auf Informationen zu reagieren,\n"
                "daher ist das Spiel ein zuverlässiger Indikator für das persönliche können und hilft \n"
                "sich in dieser Domäne zu verbessern.";
        _gameRules = "Ein Text wird angezeigt, der eine Zeugenaussage oder andere detaillierte Informationen enthält.\n"
                     "Der User hat 30 Sekunden Zeit, sich den Text durchzulesen und so viele Details wie möglich zu merken.\n"
                     "Nach Ablauf der Zeit verschwindet der Text und es werden Detailfragen zum jeweiligen Text gestellt.\n"
                     "Versuche, so viele Fragen wie möglich richtig zu beantworten!"
                     "Beachte die Rechtschreibung und schreibe zahlen aus ";
        _gameControls = "Linke Maustaste um das Feld in das du schreiben möchtest auszuwählen\n"
                        "Tastatur um deine Antwort einzugeben.";
    }

    void Remembering::render() {
        ui_elements::InfoBox(_showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
            start();
        }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endboxTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endboxText));

            ui_elements::Centered([this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    start();
                }

                if (ImGui::Button("Zurück zur Startseite")) {
                    scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                }
            });
        });

        if (_isGameRunning) {
            renderGame();
        }
    }

    void Remembering::renderGame() {
        ui_elements::Window("Remembering Game").render([this]() {
            //Logik

        });
    }

    void Remembering::start() {
        reset();
        _isGameRunning = true;
        _showEndbox = false;
    }

    void Remembering::stop() {
        _isGameRunning = false;
    }

    void Remembering::reset() {
        std::fill(_userTextBuffer.begin(), _userTextBuffer.end(), 0);
    }


    void Remembering::updateStatistics() {
        // add code here
    }

}

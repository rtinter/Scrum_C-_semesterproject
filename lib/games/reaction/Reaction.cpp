#include "Reaction.hpp"

#include <Centered.hpp>
#include <Colors.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <random>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <iostream>
#include <sstream>

namespace reaction {
    Reaction::Reaction() {
        _gameName = "Reaction";
        _gameDescription =
                "Unser Reaktionszeit-Spiel bewertet die Fähigkeit, schnell und präzise auf visuelle Reize zu reagieren,\n"
                "was für Polizei- und Feuerwehrarbeit unerlässlich ist.\n"
                "In diesen Berufen ist es entscheidend, rasch auf sich ändernde Situationen zu reagieren, \n"
                "daher ist das Spiel ein zuverlässiger Indikator für die persönliche Eignung.\n";
        _gameRules = "Der Bildschirm zeigt zunächst eine rote Farbe.\n"
                "Nach einer zufälligen Zeitspanne von bis zu 5 Sekunden wechselt der Bildschirm auf Grün.\n"
                "Sobald der Bildschirm Grün wird, klickst du so schnell wie möglich die linke Maustaste.\n"
                "Deine Reaktionszeit wird in Millisekunden angezeigt.\n"
                "Versuche, deine beste Zeit zu schlagen!";
        _gameControls = "Linke Maustaste: Klicken, sobald der Bildschirm Grün wird.";
    }

    void Reaction::render() {
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

    std::string Reaction::_endBoxTitleString {};
    std::string Reaction::_endBoxTextString {};


    void Reaction::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ui_elements::Window("Reaction Game").render([this]() {
            if (_colorClock.getElapsedTime().asSeconds() >= _redDuration && !isGreen()) {
                _windowColor = commons::Colors::GREEN;
                _startPoint = std::chrono::steady_clock::now();
            }

            if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                if (isGreen()) {
                    _isGameRunning = false;
                    _finishPoint = std::chrono::steady_clock::now();

                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        _finishPoint - _startPoint).count();

                    _showEndbox = true;

                    // convert long long duration to string
                    std::stringstream durationStream;
                    durationStream << duration;

                    _endBoxTitleString = "Vergangene Zeit: " + durationStream.str() + "ms";
                    _endboxTitle = _endBoxTitleString.c_str();

                    _endBoxTextString = "Bewertung: " + getDurationRating(duration);
                    _endboxText = _endBoxTextString.c_str();
                } else {
                    _isGameRunning = false;
                    _showEndbox = true;
                    _endboxTitle = "Zu früh geklickt!";
                }
            }
        });
        ImGui::PopStyleColor();
    }

    void Reaction::start() {
        std::random_device rd; // Seed the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister engine
        std::uniform_int_distribution<> dis(2000, 5000);

        _isGameRunning = true;
        _showEndbox = false;

        _redDuration = static_cast<float>(dis(gen)) / 1000.0f;
        _windowColor = commons::Colors::RED;
        _colorClock.restart();
    }

    void Reaction::stop() {
        _isGameRunning = false;
    }

    void Reaction::reset() {
        _windowColor = commons::Colors::RED;
        _isGameRunning = false;

        // Use <random> for better random number generation
        std::random_device rd; // Seed the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister engine
        std::uniform_int_distribution<> dis(2000, 10000);

        _redDuration = static_cast<float>(dis(gen)) / 1000.0f;
        _colorClock.restart();
    }

    std::string Reaction::getDurationRating(int duration) {
        if (duration < 260) {
            return "Herausragend";
        }
        if (duration < 340) {
            return "Super Schnell";
        }
        if (duration < 540) {
            return "Guter Durchschnitt";
        }
        if (duration < 640) {
            return "Ganz OK";
        }
        return "Langsam";
    }


    void Reaction::updateStatistics() {
        // add code here
    }

    bool Reaction::isGreen() const {
        return _windowColor.x == commons::Colors::GREEN.x && _windowColor.y == commons::Colors::GREEN.y
               && _windowColor.z == commons::Colors::GREEN.z && _windowColor.w == commons::Colors::GREEN.w;
    }

    std::string Reaction::getName() const {
        return _gameName;
    }
} // reaction

#include "Reaction.hpp"

#include <Colors.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <random>
#include <TextCentered.hpp>
#include <Window.hpp>
#include "GameSessionManager.hpp"
#include <sstream>
#include <SoundPolice.hpp>

namespace games {
    Reaction::Reaction() : abstract_game::Game(abstract_game::GameID::REACTION) {
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
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();

        ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            start();
        }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }


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

                    commons::SoundPolice::safePlaySound(commons::Sound::CLICK);

                    auto const duration {std::chrono::duration_cast<std::chrono::milliseconds>(
                            _finishPoint - _startPoint).count()};

                    _showEndBox = true;
                    _statisticResult = duration;
                    updateStatistics();

                    // convert long long duration to string
                    std::stringstream durationStream;
                    durationStream << duration;

                    _endBoxTitle =
                            "Vergangene Zeit: " + durationStream.str() + "ms";

                    _endBoxText =
                            "Bewertung: " + getDurationRating(duration);
                } else {
                    _isGameRunning = false;
                    _showEndBox = true;
                    _endBoxTitle = "Zu früh geklickt!";
                    _endBoxText = "Versuche es nochmal!";

                    commons::SoundPolice::safePlaySound(commons::Sound::ERROR);
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
        _showEndBox = false;

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
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("ms", _statisticResult);
    }

    bool Reaction::isGreen() const {
        return _windowColor.x == commons::Colors::GREEN.x && _windowColor.y == commons::Colors::GREEN.y
               && _windowColor.z == commons::Colors::GREEN.z && _windowColor.w == commons::Colors::GREEN.w;
    }

    std::string Reaction::getName() const {
        return Game::getName();
    }
} // reaction

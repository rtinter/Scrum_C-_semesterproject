#include "Reaction.hpp"

#include <iostream>
#include <Overlay.hpp>
#include <Window.hpp>

#include "SFML/Graphics/Text.hpp"
#include "Colors.hpp"


namespace reaction {
    Reaction::Reaction() : _isOpen{false} {
        _size = {ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 90};

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
        bool showGame{true};

        if (showGame) {
            start();
        }

    }

    void Reaction::start() {
        if (_colorClock.getElapsedTime().asSeconds() >= _redDuration && _isRunning && _isRed) {
            turnGreen();
        }

        ImGui::SetNextWindowSize(_size);
        ImGui::SetWindowPos(ImVec2(0, 90));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ImGui::Begin("Reaction Game", nullptr);
        if (ImGui::IsWindowHovered()
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            reset();
        }

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!_isRed) {
                _isRunning = false;
                _finishPoint = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                    _finishPoint - _startPoint).count();
                std::cout << "Time elapsed: " << duration << " ms" << std::endl;
                std::cout << "Duration rating: " << getDurationRating(duration) << std::endl;
            } else {
                std::cout << "Zu früh geklickt!" << std::endl;
            }
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }

    void Reaction::reset() {
        _isRed = true;
        _isRunning = true;
        _windowColor = commons::Colors::RED;

        // Use <random> for better random number generation
        std::random_device rd; // Seed the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister engine
        std::uniform_int_distribution<> dis(0, 5000); // Uniform distribution between 0 and 5000 milliseconds

        _redDuration = static_cast<float>(dis(gen)) / 1000.0f; // Random duration between 0 and 5 seconds
        _colorClock.restart();
        std::cout << "Start Game!" << std::endl;
    }

    void Reaction::turnGreen() {
        _windowColor = commons::Colors::GREEN; // Change window color to green
        _isRed = false;
        _startPoint = std::chrono::steady_clock::now();
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
} // reaction

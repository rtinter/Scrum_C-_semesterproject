//
// Created by zepi on 16.05.24.
//

#include "Reaction.hpp"
#include "SFML/Graphics/Text.hpp"


namespace reaction {
    Reaction::Reaction() : _size{ImGui::GetIO().DisplaySize}, _isRunning{false} {


    Reaction::Reaction() : _isOpen{true}, _isRed{true}, _wasReset{false} {

        _gameName = "Reaction";
        _gameDescription = "Reaction ist ein einfaches, aber spannendes Spiel, das deine Reflexe auf die Probe stellt.\n"
                           "Warte, bis der Bildschirm von Rot zu Grün wechselt, und klicke so schnell wie möglich die linke Maustaste, um deine Reaktionszeit in Millisekunden zu messen.";
        _gameRules = "Der Bildschirm zeigt zunächst eine rote Farbe.\n"
                     "Nach einer zufälligen Zeitspanne von bis zu einer Minute wechselt der Bildschirm auf Grün.\n"
                     "Sobald der Bildschirm Grün wird, klickst du so schnell wie möglich die linke Maustaste.\n"
                     "Deine Reaktionszeit wird in Millisekunden angezeigt.\n"
                     "Versuche, deine beste Zeit zu schlagen!";
        _gameControls = "Linke Maustaste: Klicken, sobald der Bildschirm Grün wird.";

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

    void Reaction::reset() {        //is (currently) activated by pressing the right mouse button!
        //Also currently used to start the game itself once the game window is open
        //Is called in Reaction::start() when the left mouse button is pressed

    }

    void Reaction::start() {
        if (!_isOpen) reset();
        _isOpen = true;
        render();
    }

    void Reaction::reset() {
        _isRed = true;
        _isRunning = true;
        _windowColor = commons::Colors::kRED;
        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        _redDuration = static_cast<float>(std::rand() % 5000) / 1000.0f; // Random duration between 0 and 5 seconds
        _colorClock.restart();
    }

    void Reaction::render() {
        if (_colorClock.getElapsedTime().asSeconds() >= _redDuration && _isRunning) {
            turnGreen();
        }

        if (ImGui::IsWindowHovered()
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            std::cout << "test";
            reset();
        }
        sf::Event event;
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::MouseButtonPressed && !_isRed) {
            std::cout << "test2";
            _isRunning = false;
            _finishPoint = std::chrono::high_resolution_clock::now();
            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(
                    _finishPoint - _startPoint).count() << " ms" << std::endl;
            std::cout << "Duration rating: " << getDurationRating(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                            _finishPoint - _startPoint).count()) << std::endl;
        }

        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ImGui::SetNextWindowSize(_size);
        ImGui::Begin("Reaction Game", nullptr);
        ImGui::PopStyleColor();
        ImGui::End();
    }

    void Reaction::turnGreen() {
        _windowColor = commons::Colors::kGREEN; // Change window color to green
        _isRed = false;
        _startPoint = std::chrono::high_resolution_clock::now(); //
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

    }


} // reaction



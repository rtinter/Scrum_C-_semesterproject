//
// Created by zepi on 16.05.24.
//

#include "Reaction.hpp"
#include "SFML/Graphics/Text.hpp"


namespace reaction {
    Reaction::Reaction() : _size{ImGui::GetIO().DisplaySize}, _isOpen{false} {

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
        std::cout << "Start Game!" << std::endl;
    }

    void Reaction::render() {
        if (_colorClock.getElapsedTime().asSeconds() >= _redDuration && _isRunning && _isRed) {
            turnGreen();
        }
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ImGui::SetNextWindowSize(_size);
        ImGui::Begin("Reaction Game", nullptr);

        if (ImGui::IsWindowHovered()
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            reset();
        }

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!_isRed) {
                _isRunning = false;
                _finishPoint = std::chrono::high_resolution_clock::now();
                std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(
                        _finishPoint - _startPoint).count() << " ms" << std::endl;
                std::cout << "Duration rating: " << getDurationRating(
                        std::chrono::duration_cast<std::chrono::milliseconds>(
                                _finishPoint - _startPoint).count()) << std::endl;
            } else {
                std::cout << "Zu früh geklickt!" << std::endl;

            }
        }

        ImGui::PopStyleColor();
        ImGui::End();
    }

    void Reaction::turnGreen() {
        _windowColor = commons::Colors::kGREEN; // Change window color to green
        _isRed = false;
        _startPoint = std::chrono::high_resolution_clock::now();
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



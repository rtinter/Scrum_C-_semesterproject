//
// Created by zepi on 16.05.24.
//

#include "Reaction.hpp"
#include "SFML/Graphics/Text.hpp"


namespace reaction {

    Reaction::Reaction() : _isOpen{true} {


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

        _windowColor = commons::Colors::kRED; // Change window color back to red
        _redDuration = static_cast<float>(std::rand() % 5000) / 1000.0f; // Random duration between 0 and 5 seconds
        _colorClock.restart();
        _isRed = true;

    }

    void Reaction::updateStatistics() {

    }


    void Reaction::start() {


        _isRunning = true;

        _size = ImGui::GetIO().DisplaySize;
        ImGui::SetNextWindowSize(_size);


        ImGui::Begin("Reaction Game", nullptr);



        _windowColor = sf::Color::Black;
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);

        _isRed = false;
        _redDuration = 0.0f;

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        if (ImGui::IsWindowHovered()
            && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            reset();
        }
        if (ImGui::IsWindowHovered()
            && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !_isRed) {
            _finishPoint = std::chrono::high_resolution_clock::now();
            _windowColor = commons::Colors::kRED; // Change window color to blue
            std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(
                    _finishPoint - _startPoint).count() << " ms" << std::endl;
            std::cout << "Duration rating: " << getDurationRating(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                            _finishPoint - _startPoint).count()) << std::endl;
        }


        // Check if the red duration has passed
        if (_isRed && _colorClock.getElapsedTime().asSeconds() >= _redDuration) {
            _windowColor = commons::Colors::kGREEN; // Change window color to green
            _startPoint = std::chrono::high_resolution_clock::now();
            _isRed = false;
        }

        ImGui::End();

    }


} // reaction



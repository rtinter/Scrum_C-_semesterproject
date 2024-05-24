//
// Created by zepi on 16.05.24.
//

#include "Reaction.hpp"
#include "SFML/Graphics/Text.hpp"




namespace reaction {

    Reaction::Reaction(ImVec2 const &size) :  _size{size}, _isOpen{true} {


    }

    std::string Reaction::getDurationRating(int duration) {
        if (duration < 260) {
            return "Herausragend";
        } else if (duration < 340) {
            return "Super Schnell";
        } else if (duration < 540) {
            return "Guter Durchschnitt";
        } else if (duration < 640) {
            return "Ganz OK";
        } else {
            return "Langsam";
        }
    }

    void Reaction::reset() {        //is (currently) activated by pressing the right mouse button!
        //Also currently used to start the game itself once the game window is open

        _windowColor = sf::Color::Red; // Change window color back to red
        _redDuration = static_cast<float>(std::rand() % 5000) / 1000.0f; // Random duration between 0 and 5 seconds
        _colorClock.restart();
        _isRed = true;

    }

    void Reaction::updateStatistics() {

    }



    void Reaction::start() {
        sf::RenderWindow window(sf::VideoMode(2 * 640, 1.5 * 480), "ImGui + SFML = <3");
        window.setFramerateLimit(60);
        ImGui::SFML::Init(window);

        _isRunning = true;

        ImGui::SetNextWindowSize(ImVec2(1100.f, 600.f));
        ImGui::Begin("Reaction Game");
        ImGui::End();



        _windowColor = sf::Color::Black;
        // Display white text "Click to start" in the center of the window
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text("Click to start", font);



        _isRed = false;
        _redDuration = 0.0f;

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);

                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Right && !_isRed) {
                        reset();
                    }
                    if (event.mouseButton.button == sf::Mouse::Left && !_isRed) {
                        _finishPoint = std::chrono::high_resolution_clock::now();
                        _windowColor = sf::Color::Red; // Change window color to blue
                        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(_finishPoint - _startPoint).count() << " ms" << std::endl;
                        std::cout << "Duration rating: " << getDurationRating(std::chrono::duration_cast<std::chrono::milliseconds>(_finishPoint - _startPoint).count() ) << std::endl;
                    }
                }
            }

            // Check if the red duration has passed
            if (_isRed && _colorClock.getElapsedTime().asSeconds() >= _redDuration) {
                _windowColor = sf::Color::Green; // Change window color to green
                _startPoint = std::chrono::high_resolution_clock::now();
                _isRed = false;
            }



            ImGui::SFML::Update(window, _deltaClock.restart());

            ImGui::ShowDemoWindow();


            window.clear(_windowColor); // Use the window color variable
            ImGui::SFML::Render(window);
            window.display();
        }

        ImGui::SFML::Shutdown();

    }


} // reaction

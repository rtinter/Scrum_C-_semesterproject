//
// Created by zepi on 16.05.24.
//

#include "Reaction.hpp"
#include "SFML/Graphics/Text.hpp"




namespace reaction {

    Reaction::Reaction(ImVec2 const &size) :  size{size}, isOpen{true} {


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

        windowColor = sf::Color::Red; // Change window color back to red
        redDuration = static_cast<float>(std::rand() % 5000) / 1000.0f; // Random duration between 0 and 5 seconds
        colorClock.restart();
        isRed = true;

    }

    void Reaction::updateStatistics() {

    }

    void Reaction::start2() {
        ImGui::SetNextWindowSize(ImVec2(1100.f, 600.f));
        ImGui::Begin("Font & Color Example");

        /* Font Example */
        ImGui::PushFont(commons::Fonts::_header1);
        ImGui::Text("Header 1");
        ImGui::PopFont();

        ImGui::PushFont(commons::Fonts::_header2);
        ImGui::Text("Header 2");
        ImGui::PopFont();


        windowColor = sf::Color::Black;
        // Display white text "Click to start" in the center of the window
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text("Click to start", font);
        }

    void Reaction::start() {
        sf::RenderWindow window(sf::VideoMode(2 * 640, 1.5 * 480), "ImGui + SFML = <3");
        window.setFramerateLimit(60);
        ImGui::SFML::Init(window);

        isRunning = true;

        ImGui::SetNextWindowSize(ImVec2(1100.f, 600.f));
        ImGui::Begin("Reaction Game");
        ImGui::End();



        windowColor = sf::Color::Black;
        // Display white text "Click to start" in the center of the window
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text("Click to start", font);



        isRed = false;
        redDuration = 0.0f;

        // Seed the random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);

                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Right && !isRed) {
                        reset();
                    }
                    if (event.mouseButton.button == sf::Mouse::Left && !isRed) {
                        finishPoint = std::chrono::high_resolution_clock::now();
                        windowColor = sf::Color::Blue; // Change window color to blue
                        std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(finishPoint - startPoint).count() << " ms" << std::endl;
                        std::cout << "Duration rating: " << getDurationRating(std::chrono::duration_cast<std::chrono::milliseconds>(finishPoint - startPoint).count() ) << std::endl;
                    }
                }
            }

            // Check if the red duration has passed
            if (isRed && colorClock.getElapsedTime().asSeconds() >= redDuration) {
                windowColor = sf::Color::Green; // Change window color to green
                startPoint = std::chrono::high_resolution_clock::now();
                isRed = false;
            }



            ImGui::SFML::Update(window, deltaClock.restart());

            ImGui::ShowDemoWindow();


            window.clear(windowColor); // Use the window color variable
            ImGui::SFML::Render(window);
            window.display();
        }

        ImGui::SFML::Shutdown();

    }


} // reaction

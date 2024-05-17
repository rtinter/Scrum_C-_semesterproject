#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib> // For std::rand and std::srand
#include <ctime>   // For std::time
#include <chrono>  // For std::chrono
#include <iostream>

std::string getDurationRating(int duration) {
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

int main() {
    sf::RenderWindow window(sf::VideoMode(2*640, 1.5*480), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    sf::Color windowColor = sf::Color::Black;
    sf::Clock deltaClock;
    sf::Clock colorClock; // Clock to track the duration of the color change
    bool isRed = false;
    float redDuration = 0.0f;
    std::chrono::time_point<std::chrono::system_clock> start, finish;

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
                    windowColor = sf::Color::Red; // Change window color to red
                    redDuration = static_cast<float>(std::rand() % 5000) / 1000.0f; // Random duration between 0 and 5 seconds
                    colorClock.restart();
                    isRed = true;
                }
                if (event.mouseButton.button == sf::Mouse::Left && !isRed) {
                    finish = std::chrono::high_resolution_clock::now();
                    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << " ms" << std::endl;
                    std::cout << "Duration rating: " << getDurationRating(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() ) << std::endl;
                }
            }
        }

        // Check if the red duration has passed
        if (isRed && colorClock.getElapsedTime().asSeconds() >= redDuration) {
            windowColor = sf::Color::Green; // Change window color to green
            start = std::chrono::high_resolution_clock::now();
            isRed = false;
        }



        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::ShowDemoWindow();


        window.clear(windowColor); // Use the window color variable
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

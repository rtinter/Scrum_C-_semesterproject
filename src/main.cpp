#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <random>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1280), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

/*
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
*/
    sf:
    sf::Clock deltaClock;
    sf::Clock reactionTimer; // Timer for the reaction game
    std::mt19937 rng(std::random_device{}()); // Random number generator
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,8000); // Distribution range between 0 and 8000 milliseconds

    float randomTime = dist6(rng); // Time to wait before changing to green
    bool switchedToGreen = false; // State to track if the color has switched to green

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //ImGui::ShowDemoWindow();


        window.clear();
        /*window.draw(shape);*/
        ImGui::SFML::Render(window);
        window.display();
    }
}
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Athena");
    window.setFramerateLimit(60);
    bool isColorRed {true};
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
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


        ImGui::Begin("React-Game-Window");

        //React-Game


        ImGui::Button("Look at this pretty button");
        if (ImGui::Button("Click me")) {
            std::cout << "You clicked the button!" << std::endl;
            if (isColorRed)
                isColorRed = false;
            else
                isColorRed = true;
        }


        ImGui::End();

        if (isColorRed) {
            window.clear(sf::Color::Red);
        } else {
            window.clear(sf::Color::Green);
        }

        //window.clear(sf::Color::Red);
        ImGui::SFML::Render(window);
        window.display();
    }
}
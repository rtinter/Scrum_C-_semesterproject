#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Tile.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    ui_elements::Tile tileItem(200, 300, ImVec4(0.39f, 0.58f, 0.93f, 1.0f), "Pictogram", "Spielname", "Beschreibung");


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
        tileItem.render();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
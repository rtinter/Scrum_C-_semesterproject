#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "iostream"
#include "Tile.h"
#include "Dashboard.hpp"
#include "Header.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    views::Dashboard dashboard;
    //Testcallback funktion, da atm keine Logik
    Header header("Home", "Meine Stats", []() {
        std::cout << "Stats button clicked!" << std::endl;
    });

    // Füge Tiles zur Kategorie 1 hinzu
    dashboard.addTileToCategory1(ui_elements::Tile(300, 400, "Pictogram", "Spielname", "Beschreibung"));
    dashboard.addTileToCategory1(ui_elements::Tile(300, 400, "Pictogram", "Spielname", "Beschreibung"));

    // Füge Tiles zur Kategorie 2 hinzu
    dashboard.addTileToCategory2(ui_elements::Tile(300, 400, "Pictogram", "Spielname", "Beschreibung"));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();

        header.render();
        dashboard.render();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

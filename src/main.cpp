#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "iostream"
#include "Tile.h"
#include "Dashboard.hpp"
#include "Header.hpp"
#include "StyleManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);
    commons::StyleManager::loadStyle();

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

        /* Style Example */
        ImGui::ShowDemoWindow();

        /* Font Example*/
        ImGui::SetNextWindowSize(ImVec2(1100.f, 400.f));
        ImGui::Begin("Font Example");

        ImGui::PushFont(commons::StyleManager::getFont(commons::Font::HEADER1));
        ImGui::Text("Header 1");
        ImGui::PopFont();

        ImGui::PushFont(commons::StyleManager::getFont(commons::Font::HEADER2));
        ImGui::Text("Header 2");
        ImGui::PopFont();

        ImGui::PushFont(commons::StyleManager::getFont(commons::Font::HEADER3));
        ImGui::Text("Header 3");
        ImGui::PopFont();

        ImGui::PushFont(commons::StyleManager::getFont(commons::Font::BODY));
        ImGui::Text("Body:\n"
                    "Lorem ipsum dolor sit amet, consetetur sadipscing elitr,\n"
                    "sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\n"
                    "\At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren.\n"
                    "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam");
        ImGui::PopFont();

        ImGui::End();


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}

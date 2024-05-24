#include "App.hpp"
#include "StyleManager.hpp"
#include "Dashboard.hpp"
#include "Header.hpp"

#include <iostream>
#include <imgui-SFML.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


const int App::kWINDOW_WIDTH{1920};
const int App::kWINDOW_HEIGHT{1080};
const std::string App::kTITLE{"Human Benchmark"};
const int App::kFRAME_RATE{60};


void App::start() {
    sf::RenderWindow window(sf::VideoMode(App::kWINDOW_WIDTH, kWINDOW_HEIGHT), App::kTITLE);
    window.setFramerateLimit(App::kFRAME_RATE);



    if (!ImGui::SFML::Init(window)) {
        // Initialisierung fehlgeschlagen
        return;
    }

    //load the styleManager to adjust Colors etc.
    commons::StyleManager::loadStyle();

    views::Dashboard dashboard;
    //Testcallback funktion, da atm keine Logik
    Header header("Home", "Meine Stats", []() {
        std::cout << "Stats button clicked!" << std::endl;
    });

    // define each needed tile for the games
    const std::vector<ui_elements::Tile> kCategory1Tiles = {
        ui_elements::Tile("Pictogram1", "Spielname1", "Beschreibung1", []() {
             // button action to run (render) the game
        }),
        ui_elements::Tile("Pictogram2", "Spielname2", "Beschreibung2", []() {}),
    };

    const std::vector<ui_elements::Tile> kCategory2Tiles = {
        ui_elements::Tile("Pictogram3", "Spielname3", "Beschreibung3", []() {}),
    };
    //add tiles to the category
    dashboard.addTilesToCategory("Kategorie 1", kCategory1Tiles);
    dashboard.addTilesToCategory("Kategorie 2", kCategory2Tiles);
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
        window.clear();

        //render header and dashboard
        header.render();
        dashboard.render();

        /* Style Example */
        //ImGui::ShowDemoWindow();

        ImGui::SFML::Render(window);
        window.display();
    }


    ImGui::SFML::Shutdown();
}

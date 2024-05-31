#include "App.hpp"
#include "StyleManager.hpp"
#include "Dashboard.hpp"
#include "Header.hpp"

#include <iostream>
#include <imgui-SFML.h>
#include <StatisticsGameTable.hpp>
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

    std::vector<std::string> values{"Datum", "Duration", "Session", "Geschwindigkeit"};
    std::vector<std::string> values_10{"Datum", "Duration", "Session", "Geschwindigkeit", "Obrigkeit", "Untrigkeit"};
    std::vector<std::string> values2{"1.1.1111 11:11", "12", "1", "10mm"};
    std::vector<std::string> values_11{"1.1.1111 11:11", "12", "1", "10mm", "wir", "wir nach Donnerstag"};
    std::vector<std::string> values1{"1.1.1111 11:11", "12", "41", "102mm"};
    std::vector<std::string> values3{"1.1.1111 11:11", "12", "21", "10mm"};
    std::vector<std::string> values4{"1.1.1111 11:11", "123", "31", "10mm"};
    std::map<int, std::vector<std::string>> myMap;
    std::map<int, std::vector<std::string>> myMap2;

    myMap2[0] = values_10;
    for(int i =1; i<100;i++) {
        std::vector<std::string> values_11{"1.1.1111 11:1" + std::to_string(i), "12", std::to_string(i), std::to_string(i*i), "wir", "wir nach Donnerstag"};
        myMap2[i] = values_11;
    }
    myMap2[101] = {"1.1.1111 11:1" + std::to_string(101), "12"};

    ui_elements::StatisticsGameTable table(myMap2);
    //ui_elements::StatistikGameTabelle table("32.2.1202", "42", "viele");
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
        //header.render();
        //dashboard.render();
        table.render();

        /* Style Example */
        //ImGui::ShowDemoWindow();

        ImGui::SFML::Render(window);
        window.display();
    }


    ImGui::SFML::Shutdown();
}

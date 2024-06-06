#include "App.hpp"

#include <imgui-SFML.h>
#include <iostream>

#include "StyleManager.hpp"
#include "Dashboard.hpp"
#include "Header.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <stack>

#include "Reaction.hpp"


const int App::WINDOW_WIDTH{1920};
const int App::WINDOW_HEIGHT{1080};
const std::string App::TILE{"Human Benchmark"};
const int App::FRAME_RATE{60};
bool App::_showGame{false};

std::stack<std::function<void()>> openWindows;

void closeLastWindow() {
    if (!openWindows.empty()) {
        openWindows.top()();
        openWindows.pop();
    }
}

void App::start() {
    sf::RenderWindow window(sf::VideoMode(App::WINDOW_WIDTH, WINDOW_HEIGHT), App::TILE);
    window.setFramerateLimit(App::FRAME_RATE);


    if (!ImGui::SFML::Init(window)) {
        // Initialisierung fehlgeschlagen
        return;
    }

    //load the styleManager to adjust Colors etc.
    commons::StyleManager::loadStyle();

    views::Dashboard dashboard;
    //Testcallback funktion, da atm keine Logik
    Header header("Home", "Zurück", []() {
        closeLastWindow();
        std::cout << "Stats button clicked!" << std::endl;
    });

    // define each needed tile for the games
    const std::vector<ui_elements::Tile> kCategory1Tiles = {
            ui_elements::Tile("Pictogram1", "Reaktionsspiel", "Beschreibung1", []() {
                _showGame = true;
                openWindows.push([]() { _showGame = false; });
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

    reaction::Reaction reactionGame;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();

        dashboard.render();
        if (_showGame) {
            reactionGame.render();
        }

        /* Style Example */
        //ImGui::ShowDemoWindow();



        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

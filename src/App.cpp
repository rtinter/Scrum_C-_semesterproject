#include "App.hpp"
#include "StyleManager.hpp"
#include "Header.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "GameScene.hpp"

#include <iostream>
#include <imgui-SFML.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>


const int App::WINDOW_WIDTH{1920};
const int App::WINDOW_HEIGHT{1080};
const std::string App::TILE{"Human Benchmark"};
const int App::FRAME_RATE{60};


void App::start() {
    sf::RenderWindow window(sf::VideoMode(App::WINDOW_WIDTH, WINDOW_HEIGHT), App::TILE);
    window.setFramerateLimit(App::FRAME_RATE);

    SceneManager& sceneManager {SceneManager::getInstance()};
    sceneManager.addDefaultScenes();

    if (!ImGui::SFML::Init(window)) {
        // Initialisierung fehlgeschlagen
        return;
    }

    //load the styleManager to adjust Colors etc.
    commons::StyleManager::loadStyle();

    views::Dashboard dashboard;
    //Testcallback funktion, da atm keine Logik
    views::Header header("Home", "Meine Stats", []() {
        std::cout << "Stats button clicked!" << std::endl;
    });
    sf::Clock deltaClock;
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
        sceneManager.render();

        //render header and dashboard
         // header.render();
        // dashboard.render();

        /* Style Example */
        //ImGui::ShowDemoWindow();

        ImGui::SFML::Render(window);
        window.display();
    }


    ImGui::SFML::Shutdown();
}

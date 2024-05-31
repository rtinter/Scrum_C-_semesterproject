#include "App.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "GameScene.hpp"

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
        return;
    }

    commons::StyleManager::loadStyle();

    // Register scenes
    SceneManager& sceneManager = SceneManager::getInstance();
    sceneManager.addScene("DashboardScene", std::make_unique<DashboardScene>());
    sceneManager.addScene("GameScene", std::make_unique<GameScene>());

    // Start with the Dashboard scene
    sceneManager.switchTo("DashboardScene");

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

        // Render the current scene
        sceneManager.render();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

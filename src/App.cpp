#include "App.hpp"
#include <imgui-SFML.h>
#include <SceneManager.hpp>
#include <StyleManager.hpp>
#include <SoundManager.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"


const int App::WINDOW_WIDTH{1920};
const int App::WINDOW_HEIGHT{1080};
const std::string App::TILE{"Human Benchmark"};
const int App::FRAME_RATE{60};

void App::start() {
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::RenderWindow window(videoMode, TILE);
    window.setFramerateLimit(FRAME_RATE);

    //init singleton and start Dashboard
    scene::SceneManager &sceneManager{scene::SceneManager::getInstance()};
    sceneManager.addDefaultScenes();

    if (!ImGui::SFML::Init(window)) {
        // Initialisierung fehlgeschlagen
        return;
    }

#if (defined(_WIN32))
    // load the sounds
    commons::SoundManager::loadSounds();
#endif


    // load the styleManager to adjust Colors etc.
    commons::StyleManager::loadStyle();
    sf::Clock deltaClock;

    while (window.isOpen()) {
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();

        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sceneManager.render();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

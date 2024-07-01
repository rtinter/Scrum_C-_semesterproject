#include "App.hpp"

#include <imgui-SFML.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Logger.hpp"
#include "MemoryGameImageManager.hpp"
#include "LogType.hpp"
#include "SceneManager.hpp"
#include "StyleManager.hpp"
#include "WindowConfig.hpp"

#if (defined(_WIN32))

#include "SoundManager.hpp"

#endif

void App::start() {

    // Initialize ImageManager singleton
    memory::MemoryGameImageManager::getInstance().initialize();

    logger::createLogDir("logs");

    logger::Logger &logger{logger::Logger::getInstance()};
    logger << logger::LogType::INFORMATION;
    logger << "App Start";

    sf::VideoMode videoMode(commons::WindowConfig::WINDOW_WIDTH, commons::WindowConfig::WINDOW_HEIGHT);
    sf::RenderWindow window(videoMode, commons::WindowConfig::TILE, sf::Style::Close);
    window.setFramerateLimit(commons::WindowConfig::FRAME_RATE);

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
        window.clear(sf::Color(245, 242, 247, 255));

        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                logger << "App close initialized";
                window.close();
            }
        }

        sceneManager.render();

        ImGui::SFML::Render(window);
        window.display();
    }

    // Release texture resources before shutting down ImGui
    memory::MemoryGameImageManager::getInstance().releaseResources();

    ImGui::SFML::Shutdown();
    logger << "App Shutdown";
}

#include "App.hpp"
#include <imgui-SFML.h>
#include <SceneManager.hpp>
#include <StyleManager.hpp>
#include <SoundManager.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

#include "Logger.hpp"
#include "QueueEntryType.hpp"

int const App::FRAME_RATE{60};
int const App::WINDOW_HEIGHT{1080};
int const App::WINDOW_WIDTH{1920};
std::string const App::TILE{"Human Benchmark"};

void App::start() {

    logger::Logger& logger {logger::Logger::getInstance()};
    logger << QueueEntryType::INFORMATION;
    logger << "App Start";

    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::RenderWindow window(videoMode, TILE, sf::Style::Close);
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

    ImGui::SFML::Shutdown();
    logger << "App Shutdown";
}

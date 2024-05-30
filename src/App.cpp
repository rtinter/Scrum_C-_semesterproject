#include "App.hpp"
#include "StyleManager.hpp"
#include "Dashboard.hpp"
#include "Header.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <stack>

#include "Reaction.hpp"
#include "TestScene.hpp"


const int App::kWINDOW_WIDTH{1920};
const int App::kWINDOW_HEIGHT{1080};
const std::string App::kTITLE{"Human Benchmark"};
const int App::kFRAME_RATE{60};
bool App::_showGame{false};

std::stack<std::function<void()>> openWindows;

void closeLastWindow() {
    if (!openWindows.empty()) {
        openWindows.top()();
        openWindows.pop();
    }
}

void App::start() {
    sf::RenderWindow window(sf::VideoMode(App::kWINDOW_WIDTH, kWINDOW_HEIGHT), App::kTITLE);
    window.setFramerateLimit(App::kFRAME_RATE);

    if (!ImGui::SFML::Init(window)) {
        // Initialisierung fehlgeschlagen
        return;
    }

    GameScene<reaction::Reaction> game{window};

    commons::StyleManager::loadStyle();
    sf::Clock deltaClock;

    while(window.isOpen()) {
        // processEvents();
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

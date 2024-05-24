//
// Created by zepi on 16.05.24.
//

#include "App.hpp"
#include "imgui-SFML.h"
#include "StyleManager.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"
#include "ColorTheme.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Reaction.hpp"

const int App::_windowWidth{1920};
const int App::_windowHeight{1080};
const std::string App::_title{"Human Benchmark"};
const int App::_frameRate{60};

void App::start() {
    sf::RenderWindow window(sf::VideoMode(_windowWidth, _windowHeight), _title);
    window.setFramerateLimit(_frameRate);

    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);


    commons::StyleManager::loadStyle();

    sf::Clock deltaClock;


    reaction::Reaction reactionGame;

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

        reactionGame.start();

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}

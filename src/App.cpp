//
// Created by zepi on 16.05.24.
//

#include "App.hpp"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

const int App::_windowWidth{1920};
const int App::_windowHeight{1080};
const std::string App::_title{"Human Benchmark"};
const int App::_frameRate{60};

void App::start() {
    sf::RenderWindow window(sf::VideoMode(_windowWidth, _windowHeight), _title);
    window.setFramerateLimit(_frameRate);
    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);


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
        ImGui::SFML::Render(window);
        window.display();
    }
}

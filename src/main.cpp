#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
//#include StyleManager.hpp

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    //StyleManager::loadFonts();
    //ImGuiIO &io{ImGui::GetIO()};

    //ImFont *bigFont{io.Fonts->AddFontDefault()};
    //bigFont->Scale = 3.f;

    //ImFont *veryBigFont{io.Fonts->AddFontDefault()};
    //veryBigFont->Scale = 6.f;

    // Load font from other source
    float fontSize = 18.0f; // Set font size
    //io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", fontSize); // can be replaced with other font


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

        ImGui::ShowDemoWindow();

        /*
        ImGui::Begin("test");
        ImGuiIO &io{ImGui::GetIO()};
        ImGui::PushFont(io.Fonts->Fonts[0]);
        ImGui::Text("test");
        ImGui::End();
         */

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
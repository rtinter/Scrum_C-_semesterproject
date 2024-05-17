#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Athena");
    window.setFramerateLimit(60);
    bool isColorRed {true};

    std::chrono::time_point<std::chrono::system_clock> start, finish;

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    bool showModal {false};


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

        ImGui::SFML::Update(window, deltaClock.restart());

        //ALL WIDGETS IN BETWEEN Update and Render

        //ImGui::ShowDemoWindow();
        //ImGui::ShowUserGuide();


        ImGui::Begin("Test Window");

        //React-Game

        if (ImGui::Button("Modal Popup Button")) {
            showModal = true;
        }


        if (ImGui::Button("Click me")) {
            std::cout << "You clicked the button!" << std::endl;
            if (isColorRed)
                isColorRed = false;
            else {
                isColorRed = true;
                start = std::chrono::high_resolution_clock::now();
            }
        }

        const char *testtext {""};

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                finish = std::chrono::high_resolution_clock::now();
                testtext = "MouseButton has been Pressed";
                std::chrono::duration<double> elapsed {finish - start};
                //std::cout << "Mousebutton has been pressed" << elapsed.count() << "s after the color changed to red.";
            }



        ImGui::BulletText(testtext);

        ImGui::End();

        if (showModal) {
            ImGui::SetNextWindowSize(ImVec2(1000, 600));

            ImGui::OpenPopup("Overlay??");
            showModal = false; //Zum resetten
        }

        if (ImGui::BeginPopupModal("Overlay??", NULL, ImGuiWindowFlags_NoResize)) {
            ImGui::Text("SPIELENAME");
            ImGui::Text("SPIELBESCHREIBUNG");
            ImGui::Text("SPIELREGELN");
            //ImGui::
            if (ImGui::Button("Zurück zum Menü")) {
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Spiel starten!")) {
                //noch nichts
            }
            ImGui::EndPopup();
        }

        if (isColorRed) {
            window.clear(sf::Color::Red);
        } else {
            window.clear(sf::Color::Green);
        }

        //window.clear(sf::Color::Red);
        ImGui::SFML::Render(window);
        window.display();
    }
}
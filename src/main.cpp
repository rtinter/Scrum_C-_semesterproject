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

        ImGuiStyle &imGuiStyle{ImGui::GetStyle()};
        imGuiStyle.FrameRounding = 5.0f;
        imGuiStyle.WindowRounding = 5.0f;

        ImGuiIO &io = ImGui::GetIO();
        ImFont *font1 = io.Fonts->AddFontDefault();
        ImFont *font2 = io.Fonts->AddFontFromFileTTF("path/to/another_font.ttf", 24.0f);

        ImGui::Begin("Test Window");

        //React-Game

        if (ImGui::Button("Modal Popup Button")) {
            showModal = true;
        }

        ImGui::End();

        if (showModal) {
            ImGui::SetNextWindowSize(ImVec2(1000, 600));

            ImGui::OpenPopup("Overlay");
            showModal = false; //Zum resetten
        }

        if (ImGui::BeginPopupModal("Overlay", NULL,
                                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar)) {

            ImGui::Text("TITEL: Reaktionsspiel");
            ImGui::Text(
                    "SPIELBESCHREIBUNG: Testen und verbessern Sie Ihre Reaktionsgeschwindigkeit, indem Sie so schnell wie möglich auf den Farbwechsel des Bildschirms reagieren.");
            ImGui::Text("SPIELREGELN: Spielstart:\n"
                        "\n"
                        "Starten Sie das Spiel, indem Sie auf die Schaltfläche \"Start\" klicken.\n"
                        "Warten:\n"
                        "\n"
                        "Nachdem Sie das Spiel gestartet haben, wird der Bildschirm in einer neutralen Farbe (z.B. Weiß) angezeigt.\n"
                        "Warten Sie geduldig, bis der Bildschirm seine Farbe wechselt.\n"
                        "Farbwechsel:\n"
                        "\n"
                        "Der Bildschirm wechselt zufällig nach einer bestimmten Zeitspanne seine Farbe (z.B. zu Grün).\n"
                        "Reaktion:\n"
                        "\n"
                        "Sobald der Bildschirm die Farbe wechselt, klicken Sie so schnell wie möglich mit der Maus.\n"
                        "Auswertung:\n"
                        "\n"
                        "Ihre Reaktionszeit wird in Millisekunden gemessen und angezeigt.\n"
                        "Je schneller Ihre Reaktion, desto besser Ihr Ergebnis.");

            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Red);
            if (ImGui::Button("Zurück zum Menü")) {
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Spiel starten!")) {
                //noch nichts
            }
            ImGui::PopStyleColor();

            ImGui::EndPopup();
        }

        window.clear(sf::Color::Blue);
        ImGui::SFML::Render(window);
        window.display();
    }
}
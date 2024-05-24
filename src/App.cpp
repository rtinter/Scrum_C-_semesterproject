//
// Created by zepi on 16.05.24.
//

#include "App.hpp"
#include "imgui-SFML.h"
#include "StyleManager.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"
#include "ColorTheme.hpp"
#include "Dashboard.hpp"
#include "Header.hpp"
#include "iostream"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

const int App::_windowWidth{1920};
const int App::_windowHeight{1080};
const std::string App::_title{"Human Benchmark"};
const int App::_frameRate{60};

void App::start() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);
    commons::StyleManager::loadStyle();

    sf::Clock deltaClock;

    views::Dashboard dashboard;
    //Testcallback funktion, da atm keine Logik
    Header header("Home", "Meine Stats", []() {
        std::cout << "Stats button clicked!" << std::endl;
    });

    // Füge Tiles zur Kategorie 1 hinzu
    // dashboard.addTileToCategory1(ui_elements::Tile("Pictogram", "Spielname", "Beschreibung"));
    // dashboard.addTileToCategory1(ui_elements::Tile("Pictogram", "Spielname", "Beschreibung"));

    // Füge Tiles zur Kategorie 2 hinzu
    // dashboard.addTileToCategory2(ui_elements::Tile("Pictogram", "Spielname", "Beschreibung"));

    const std::vector<ui_elements::Tile> kCategory1Tiles = {
        ui_elements::Tile("Pictogram1", "Spielname1", "Beschreibung1", []() {
             // button action to run (render) the game
        }),
        ui_elements::Tile("Pictogram2", "Spielname2", "Beschreibung2", []() {}),
    };

    const std::vector<ui_elements::Tile> kCategory2Tiles = {
        ui_elements::Tile("Pictogram3", "Spielname3", "Beschreibung3", []() {}),
    };

    dashboard.addTilesToCategory("Kategorie 1", kCategory1Tiles);
    dashboard.addTilesToCategory("Kategorie 2", kCategory2Tiles);

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

        header.render();
        dashboard.render();


        /* Style Example */
        ImGui::ShowDemoWindow();


        ImGui::SetNextWindowSize(ImVec2(1100.f, 600.f));
        ImGui::Begin("Font & Color Example");

        /* Font Example */
        ImGui::PushFont(commons::Fonts::_header1);
        ImGui::Text("Header 1");
        ImGui::PopFont();

        ImGui::PushFont(commons::Fonts::_header2);
        ImGui::Text("Header 2");
        ImGui::PopFont();

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::Text("Header 3");
        ImGui::PopFont();

        ImGui::PushFont(commons::Fonts::_body);
        ImGui::Text("Body:\n"
                    "Lorem ipsum dolor sit amet, consetetur sadipscing elitr,\n"
                    "sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\n");
        ImGui::PopFont();

        /* Color Example */
        // choose freely
        auto myColor{commons::Colors::kINDIGO};

        // or use Color from ColorTheme
        auto successColor{commons::ColorTheme::kSUCCESS_COLOR};

        // Use PushStyleColor()
        ImGui::PushStyleColor(ImGuiCol_Text, myColor);
        ImGui::Text("My Color");
        ImGui::PopStyleColor();

        // Or use TextColored()
        ImGui::TextColored(successColor, "Success Color");
        ImGui::TextColored(commons::ColorTheme::kERROR_COLOR, "Error Color");
        ImGui::TextColored(commons::ColorTheme::kWARNING_COLOR, "Warning Color");
        ImGui::TextColored(commons::ColorTheme::kINFO_COLOR, "Info Color");
        ImGui::TextColored(commons::ColorTheme::kACCENT_COLOR, "Accent Color");

        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

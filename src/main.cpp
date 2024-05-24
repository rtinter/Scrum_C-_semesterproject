#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "StyleManager.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"
#include "ColorTheme.hpp"

#include "SceneManager.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Human Benchmark");
    window.setFramerateLimit(60);

    [[maybe_unused]] auto _ = ImGui::SFML::Init(window);
    commons::StyleManager::loadStyle();

    sf::Clock deltaClock;

    manager::SceneManager sceneManager = manager::SceneManager::getInstance();
    window.getView();

    while(window.isOpen()){
        sceneManager.handleEvents(window);
        sceneManager.update();
        sceneManager.render(window);
    }

// while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            ImGui::SFML::ProcessEvent(window, event);
//
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//
//        ImGui::SFML::Update(window, deltaClock.restart());
//        window.clear();
//
//        /* Style Example */
//        ImGui::ShowDemoWindow();
//
//
//        ImGui::SetNextWindowSize(ImVec2(1100.f, 600.f));
//        ImGui::Begin("Font & Color Example");
//
//        /* Font Example */
//        ImGui::PushFont(commons::Fonts::_header1);
//        ImGui::Text("Header 1");
//        ImGui::PopFont();
//
//        ImGui::PushFont(commons::Fonts::_header2);
//        ImGui::Text("Header 2");
//        ImGui::PopFont();
//
//        ImGui::PushFont(commons::Fonts::_header3);
//        ImGui::Text("Header 3");
//        ImGui::PopFont();
//
//        ImGui::PushFont(commons::Fonts::_body);
//        ImGui::Text("Body:\n"
//                    "Lorem ipsum dolor sit amet, consetetur sadipscing elitr,\n"
//                    "sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\n");
//        ImGui::PopFont();
//
//        /* Color Example */
//        // choose freely
//        auto myColor{commons::Colors::kINDIGO};
//
//        // or use Color from ColorTheme
//        auto successColor{commons::ColorTheme::kSUCCESS_COLOR};
//
//        // Use PushStyleColor()
//        ImGui::PushStyleColor(ImGuiCol_Text, myColor);
//        ImGui::Text("My Color");
//        ImGui::PopStyleColor();
//
//        // Or use TextColored()
//        ImGui::TextColored(successColor, "Success Color");
//        ImGui::TextColored(commons::ColorTheme::kERROR_COLOR, "Error Color");
//        ImGui::TextColored(commons::ColorTheme::kWARNING_COLOR, "Warning Color");
//        ImGui::TextColored(commons::ColorTheme::kINFO_COLOR, "Info Color");
//        ImGui::TextColored(commons::ColorTheme::kACCENT_COLOR, "Accent Color");
//
//        ImGui::End();
//
//        ImGui::SFML::Render(window);
//        window.display();
//    }

    ImGui::SFML::Shutdown();
    return 0;
}

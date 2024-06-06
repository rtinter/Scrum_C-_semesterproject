#include <iostream>
#include <Overlay.hpp>
#include <imgui.h>
#include "InfoBox.h"
#include "../commons/Fonts.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"

namespace ui_elements {
    InfoBox::InfoBox(const char *game_name, const char *game_descr, const char *game_rules, const char *game_controls) {
        _game_name = game_name;
        _game_descr = game_descr;
        _game_rules = game_rules;
        _game_controls = game_controls;
    }

    // UiElement
    void InfoBox::render() {
        bool boolean{true};
        ui_elements::Overlay("Infobox", boolean).render([this]() {
            //game name
            ImGui::PushFont(commons::Fonts::_header2);
            TextCentered(std::move(_game_name));
            ImGui::PopFont();
            ImGui::Text("\n");

            //Game description
            ImGui::Text(_game_descr);

            //Game Rules
            ImGui::Text(_game_rules);

            ImGui::Text(_game_controls);
            //gets current window height and button height to place them at the bottom of our PopupWindow
            const float windowHeight = ImGui::GetWindowHeight();
            const float buttonHeight = ImGui::GetFrameHeight();
            //creates a new Position at the bottom of the the PopupWindow
            const float newPosY = windowHeight - buttonHeight - ImGui::GetStyle().ItemSpacing.y;
            //sets a new Position
            ImGui::SetCursorPosY(newPosY);
            // changes the BackgroundColor to blue
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Blue);
            Centered([]() {
                if (ImGui::Button("Zurück zum Menü")) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine();
                if (ImGui::Button("Spiel starten!")) {
                    std::cout << "Spiel startet" << std::endl;
                    //noch nichts
                }
            });


            ImGui::PopStyleColor();
        });
    }
}

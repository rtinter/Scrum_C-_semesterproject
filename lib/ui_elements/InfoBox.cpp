//
// Created by zarathustra on 23.05.24.
//
#include <Overlay.hpp>
#include <imgui.h>
#include "InfoBox.h"
#include "../commons/Colors.hpp"
#include "../commons/ColorTheme.hpp"
#include "../commons/ColorHelper.hpp"
#include "../commons/Fonts.hpp"
#include "../commons/StyleManager.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"
namespace ui_elements {
    InfoBox::InfoBox(const char *game_name, const char *game_descr, const char *game_rules, const char *game_controls) {
        _name = game_name;
        _game_descr = game_descr;
        _game_rules = game_rules;
        _game_controls = game_controls;
    }

    // UiElement
    void InfoBox::render() {
        bool boolean{true};
        ui_elements::Overlay("Infobox", boolean).render([this]() {


            TextCentered(std::move(_name));

            ImGui::Text("\n");
            ImGui::Text(_game_descr);

            ImGui::Text(_game_rules);

            ImGui::Text(_game_controls);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Black);
            if (ImGui::Button("Zurück zum Menü")) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Spiel starten!")) {
                //noch nichts




            }

            ImGui::PopStyleColor();

        });
    }
}

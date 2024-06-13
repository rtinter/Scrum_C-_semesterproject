
#include <Overlay.hpp>
#include <imgui.h>
#include "InfoBox.hpp"
#include "../commons/Fonts.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"

namespace ui_elements {
    InfoBox::InfoBox(
            abstract_game::GameID &gameID,
            bool &showOverlay,
            const char *gameName,
            const char *gameDescription,
            const char *gameRules,
            const char *gameControls,
            const std::function<void()> &startCallback
    ) : _gameID(gameID),
        _showOverlay(showOverlay),
        _gameName(gameName),
        _gameDescription(gameDescription),
        _gameRules(gameRules),
        _gameControls(gameControls),
        _startCallback(startCallback) {
    }

    void InfoBox::render() {
        Overlay("Infobox", _showOverlay).render([this]() {
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Blue);

            //game name
            ImGui::PushFont(commons::Fonts::_header2);
            TextCentered(std::move(_gameName));
            ImGui::PopFont();

            ImGui::Text(_gameDescription);
            ImGui::Text(_gameRules);
            ImGui::Text(_gameControls);

            Centered(true, false,[this] {
                if (ImGui::Button("Spiel starten!")) {
                    if (_startCallback) {
                        abstract_game::GameSessionManager::getInstance().startSession(_gameID);
                        _startCallback();
                    }
                    _showOverlay = false;
                    ImGui::CloseCurrentPopup();
                }
            });


            ImGui::PopStyleColor();
        });
    }
}

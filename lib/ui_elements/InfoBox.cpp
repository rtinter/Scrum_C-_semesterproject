#include "InfoBox.hpp"

#include <Overlay.hpp>
#include <utility>
#include <imgui.h>
#include <optional>
#include <Fonts.hpp>
#include <TextCentered.hpp>
#include <Centered.hpp>
#include <ColorHelper.hpp>
#include <SceneManager.hpp>
#include <DashboardScene.hpp>

namespace ui_elements {
    InfoBox::InfoBox(
            abstract_game::GameID &_gameID,
            bool &_showOverlay,
            std::string _overlayType,
            std::optional<std::string> _gameName,
            std::optional<std::string> _gameDescription,
            std::optional<std::string> _gameRules,
            std::optional<std::string> _gameControls,
            std::function<void()> const &_callback) :
            _gameID(_gameID),
            _showOverlay(_showOverlay),
            _overlayType(std::move(_overlayType)),
            _gameName(std::move(_gameName)),
            _gameDescription(std::move(_gameDescription)),
            _gameRules(std::move(_gameRules)),
            _gameControls(std::move(_gameControls)),
            _callback(std::move(_callback)) {
    }

    InfoBox::InfoBox(
            abstract_game::GameID &_gameID,
            bool &_showOverlay,
            std::string _overlayType,
            std::optional<std::string> _endGameTitle,
            std::optional<std::string> _endGameText,
            std::function<void()> const &_callback) :
            _gameID(_gameID),
            _showOverlay(_showOverlay),
            _overlayType(std::move(_overlayType)),
            _endGameTitle(std::move(_endGameTitle)),
            _endGameText(std::move(_endGameText)),
            _callback(std::move(_callback)) {
    }

    void InfoBox::render() {
        Overlay(_overlayType.c_str(), _showOverlay).render([this]() {
            //game name
            ImGui::PushFont(commons::Fonts::_header2);

            if (_overlayType == "Startbox") {
                TextCentered(_gameName->c_str());
            } else if (_overlayType == "Endbox") {
                TextCentered(_endGameTitle->c_str());
            }

            ImGui::PopFont();

            if (_overlayType == "Startbox") {
                ImGui::Text("%s", _gameDescription->c_str());
                ImGui::Text("%s", _gameRules->c_str());
                ImGui::Text("%s", _gameControls->c_str());
            } else if (_overlayType == "Endbox") {
                TextCentered(_endGameText->c_str());
            }


            Centered(true, false, [this] {
                if (ImGui::Button("Zurück zur Startseite")) {
                    abstract_game::GameSessionManager::endSession(); // End the session when going back
                    scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                }

                ImGui::SameLine();

                if (_overlayType == "Startbox") {
                    ImGui::PushStyleColor(ImGuiCol_Button, commons::ColorTheme::ACCENT_COLOR);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::ColorHelper::adjustBrightness(commons::ColorTheme::ACCENT_COLOR, 1.2));
                    if (ImGui::Button("Spiel starten!")) {
                        if (_callback) {
                            abstract_game::GameSessionManager::startSession(_gameID);
                            _callback();
                        }
                        _showOverlay = false;
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::PopStyleColor(2);
                } else {
                    if (ImGui::Button("Versuch es nochmal")) {
                        _callback();
                    }
                }
            });
        });
    }
}

#include "ColorMatch.hpp"
#include "Fonts.hpp"
#include "ColorTheme.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "Window.hpp"
#include "RandomPicker.hpp"
#include "ColorHelper.hpp"

namespace games {
    ColorMatch::ColorMatch() : Game(abstract_game::GameID::COLOR_MATCH) {
        _gameName = "Farb-Wort-Spiel";
        _gameDescription =
                "Unser Spiel 'Farb Wort Test' zielt darauf ab, die kognitive Flexibilität zu testen,\n"
                "eine Schlüsselkompetenz für Polizei- und Feuerwehranwärter. Dabei werden Farben als Wörter angezeigt,\n"
                "wobei die Schriftfarbe von der Bedeutung des Wortes abweicht. Der User muss schnell erkennen,\n"
                "wenn das Wort und die Farbe übereinstimmen, und daraufhin klicken.\n"
                "Durch die fortlaufende Anzeige von richtigen und falschen Antworten sowie\n"
                "eine Streak-Anzeige wird die kognitive Leistung des Users bewertet.\n"
                "Die schnelle Anpassung an unerwartete Situationen und die Fähigkeit,\n"
                "zwischen verschiedenen Reizen zu unterscheiden, sind wesentliche Fähigkeiten\n"
                "für den Einsatz von Polizei- und Feuerwehrkräften.";
        _gameRules = "Es wird zufällig zwischen zwei Spiel-Modi gewechselt: "
                     "Im Modus 'Farbwort' muss man auf den zum Farbwort passenden Farb-Button klicken.\n"
                     "Im Modus 'Schriftfarbe' muss man auf den zur Schriftfarbe passenden Text-Button klicken.\n"
                     "Dabei müssen die angezeigten Zufallswörter von links nach rechts abgearbeitet werden.";
        _gameControls = "Linke Maustaste: Klicken der richtigen Antworten in der richtigen Reihenfolge";
    }

    void ColorMatch::render() {
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();

        ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            start();
        }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void ColorMatch::renderGame() {
        ui_elements::Window("Color Match Game").render([this] {
            _timer.render();

            if (_timer.isExpiredNow()) {
                stop();
            }
            if (_isTimeForNewRandomColors) {
                pickRandomColorsText();
                pickRandomColorsImVec4();
                _isTimeForNewRandomColors = false;
            }
            ui_elements::Centered(true, false, [this] {
                switch (_currentGameMode) {
                    case GameMode::MATCH_STRING:
                        ImGui::Text("Finde die Übereinstimmung mit dem Farbwort:");
                        break;
                    case GameMode::MATCH_IMVEC4:
                        ImGui::Text("Finde die Übereinstimmung mit der Schriftfarbe:");
                        break;
                }
                ImGui::NewLine();
                displayRandomColors();
                displayColorButtons();
            });
        });
    }

    void ColorMatch::start() {
        reset();
        _currentGameMode = commons::RandomPicker::pickRandomElement(
                std::vector<GameMode>{GameMode::MATCH_STRING, GameMode::MATCH_IMVEC4});
        _isGameRunning = true;
        _showEndBox = false;
        _timer.start();
    }

    void ColorMatch::reset() {
        _isTimeForNewRandomColors = true;
        _indexOfCurrentColor = 0;
        _numberOfCorrectClicksInTotal = 0;
        _numberOfCorrectClicksSinceLastError = 0;
        _longestStreak = 0;
    }

    void ColorMatch::pickRandomColorsText() {
        _randomColorsString.clear();
        for (int i{0}; i < _numberOfRandomColors; i++) {
            _randomColorsString.emplace_back(commons::RandomPicker::pickRandomElement(_AVAILABLE_COLORS_STRING));
        }
    }

    void ColorMatch::pickRandomColorsImVec4() {
        _randomColorsImVec4.clear();
        for (int i{0}; i < _numberOfRandomColors; i++) {
            _randomColorsImVec4.emplace_back(commons::RandomPicker::pickRandomElement(_AVAILABLE_COLORS_IMVEC4));
        }
    }

    void ColorMatch::displayRandomColors() {
        // TODO@Noah: use bigger font and center
        for (int i{0}; i < _randomColorsString.size(); i++) {
            // current color has bigger font
            ImGui::PushFont(_indexOfCurrentColor == i ? commons::Fonts::_header2 : commons::Fonts::_header3);
            ImGui::PushStyleColor(ImGuiCol_Text, _randomColorsImVec4.at(i));
            ImGui::Text("%s", _randomColorsString.at(i).c_str());
            ImGui::SameLine();
            ImGui::PopStyleColor();
            ImGui::PopFont();
        }
    }

    void ColorMatch::displayColorButtons() {
        ImGui::NewLine();
        for (int i{0}; i < _AVAILABLE_COLORS_STRING.size(); i++) {
            if (_indexOfCurrentColor >= _numberOfRandomColors) {
                _isTimeForNewRandomColors = true;
                _indexOfCurrentColor = 0;
            }
            bool isCurrentColor;
            std::string buttonID;
            switch (_currentGameMode) {
                case GameMode::MATCH_STRING:
                    isCurrentColor = _AVAILABLE_COLORS_STRING.at(i) == _randomColorsString.at(_indexOfCurrentColor);
                    buttonID = "##" + _AVAILABLE_COLORS_STRING.at(i);
                    ImGui::PushStyleColor(ImGuiCol_Button, _AVAILABLE_COLORS_IMVEC4.at(i)); // Normal state
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                          _AVAILABLE_COLORS_IMVEC4.at(i)); // Hover state equals normal state
                    break;
                case GameMode::MATCH_IMVEC4:
                    isCurrentColor = commons::ColorHelper::isEqual(_AVAILABLE_COLORS_IMVEC4.at(i),
                                                                   _randomColorsImVec4.at(_indexOfCurrentColor));
                    buttonID = _AVAILABLE_COLORS_STRING.at(i);
                    ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::VERY_LIGHT_GRAY); // Normal state
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                          commons::Colors::VERY_LIGHT_GRAY); // Hover state equals normal state
                    break;
            }

            ImGui::PushStyleColor(ImGuiCol_ButtonActive, // show whether click was correct via quick color change
                                  isCurrentColor
                                  ? commons::ColorTheme::SUCCESS_COLOR
                                  : commons::ColorTheme::ERROR_COLOR);

            if (ImGui::Button(buttonID.c_str(), ImVec2(80, 40))) {
                onClick(isCurrentColor);
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
        }
    }

    void ColorMatch::onClick(bool isCurrentColor) {
        if (isCurrentColor) {
            // when incorrect button was clicked
            _indexOfCurrentColor++;
            _numberOfCorrectClicksInTotal++;
            _numberOfCorrectClicksSinceLastError++;
            _longestStreak = std::max(_numberOfCorrectClicksSinceLastError, _longestStreak);
        } else {
            // when correct button was clicked
            _numberOfCorrectClicksSinceLastError = 0;
            _timer.reduceTime(5);
        }
    }

    void ColorMatch::stop() {
        _endBoxText =
                "Richtige: " + std::to_string(_numberOfCorrectClicksInTotal) + "\nLängster Streak: " +
                std::to_string(_longestStreak);
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Zeit abgelaufen!";
        updateStatistics();
    }

    void ColorMatch::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Richtige(r)", _numberOfCorrectClicksInTotal);
    }
}

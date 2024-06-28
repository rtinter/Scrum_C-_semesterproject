#include "ColorMatch.hpp"
#include "Fonts.hpp"
#include "ColorTheme.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"
#include "Window.hpp"
#include "RandomPicker.hpp"
#include "ColorHelper.hpp"

namespace games {
    ColorMatch::ColorMatch() : Game(abstract_game::GameID::COLOR_MATCH) {
        _gameName = "Farbe & Wort";
        _gameDescription =
                "Unser Spiel 'Farbe & Wort' zielt darauf ab, die kognitive Flexibilität zu testen,\n"
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
                pickRandomColorsString();
                pickRandomColorsImVec4();
                _isTimeForNewRandomColors = false;
            }
            ui_elements::Centered(true, false, [this] {
                switch (_currentGameMode) {
                    case GameMode::MATCH_STRING:
                        ImGui::Text("Finde die Übereinstimmung mit dem FarbWORT:");
                        break;
                    case GameMode::MATCH_IMVEC4:
                        ImGui::Text("Finde die Übereinstimmung mit der SchriftFARBE:");
                        break;
                }
                ImGui::NewLine();
                ImGui::NewLine();
                displayRandomColors();
                ImGui::NewLine();
                displayAnswerButtons();
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

    /**
     * @brief Picks random elements from _availableColorsString
     */
    void ColorMatch::pickRandomColorsString() {
        _randomColorsString.clear();
        for (int i{0}; i < NUMBER_OF_RANDOM_COLORS; i++) {
            _randomColorsString.emplace_back(commons::RandomPicker::pickRandomElement(_availableColorsString));
        }
    }

    /**
     * @brief Picks random elements from _availableColorsImVec4
     */
    void ColorMatch::pickRandomColorsImVec4() {
        _randomColorsImVec4.clear();
        for (int i{0}; i < NUMBER_OF_RANDOM_COLORS; i++) {
            _randomColorsImVec4.emplace_back(commons::RandomPicker::pickRandomElement(_availableColorsImVec4));
        }
    }


    /**
     * @brief Displays color words from _randomColorsString (e.g. "rot"), using
     * the respective element from _randomColorImVec4 as font color.
     */
    void ColorMatch::displayRandomColors() {
        for (int i{0}; i < _randomColorsString.size(); i++) {
            ImGui::SameLine(0.f, 70); // some spacing
            // current color has bigger font
            ImGui::PushFont(_indexOfCurrentColor == i ? commons::Fonts::_header2 : commons::Fonts::_header3);
            ImGui::PushStyleColor(ImGuiCol_Text, _randomColorsImVec4.at(i));
            ImGui::Text("%s", _randomColorsString.at(i).c_str());
            ImGui::SameLine();
            ImGui::PopStyleColor();
            ImGui::PopFont();
        }
    }

    /**
     * @brief: Displays clickable answer buttons
     */
    void ColorMatch::displayAnswerButtons() {
        ImGui::NewLine();
        for (int i{0}; i < _availableColorsString.size(); i++) {
            // if _indexOfCurrentColor is out of range, generate new random colors and
            // start once again from index 0
            if (_indexOfCurrentColor >= NUMBER_OF_RANDOM_COLORS) {
                _isTimeForNewRandomColors = true;
                _indexOfCurrentColor = 0;
            }
            bool isCurrentColor;
            std::string buttonID;
            switch (_currentGameMode) {
                case GameMode::MATCH_STRING:
                    // create colored buttons with no label
                    isCurrentColor = _availableColorsString.at(i) == _randomColorsString.at(_indexOfCurrentColor);
                    buttonID = "##" + _availableColorsString.at(i);
                    ImGui::PushStyleColor(ImGuiCol_Button, _availableColorsImVec4.at(i)); // Normal state
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                          commons::ColorHelper::adjustBrightness(_availableColorsImVec4.at(i),
                                                                                 1.2f)); // Hover state equals normal state
                    break;
                case GameMode::MATCH_IMVEC4:
                    // create gray buttons with color names (e.g. "rot") as button labels
                    isCurrentColor = commons::ColorHelper::isEqual(_availableColorsImVec4.at(i),
                                                                   _randomColorsImVec4.at(_indexOfCurrentColor));
                    buttonID = _availableColorsString.at(i);
                    ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::VERY_LIGHT_GRAY); // Normal state
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                          commons::Colors::VERY_LIGHT_GRAY); // Hover state equals normal state
                    break;
            }

            // show whether click was correct via quick color change
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                  isCurrentColor
                                  ? commons::ColorTheme::SUCCESS_COLOR
                                  : commons::ColorTheme::ERROR_COLOR);

            if (ImGui::Button(buttonID.c_str(), ImVec2(80.f, 40.f))) {
                onClick(isCurrentColor);
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
        }
    }

    /**
     * @brief Actions that take place when an answer button was clicked -
     * depending on whether it is the correct one
     * @param isCurrentColor Was the correct button clicked?
     */
    void ColorMatch::onClick(bool const &isCurrentColor) {
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
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten",
                                                                                     _numberOfCorrectClicksInTotal);
    }
}

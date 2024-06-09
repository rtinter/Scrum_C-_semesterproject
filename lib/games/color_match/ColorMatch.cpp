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

namespace games {
    ColorMatch::ColorMatch() {
        _gameName = "Farb-Wort-Spiel";
        _gameDescription =
                "Unser Spiel 'Farb Wort Test' zielt darauf ab, die kognitive Flexibilität zu testen,\n"
                "eine Schlüsselkompetenz für Polizei- und Feuerwehranwärter. Dabei werden Farben als Wörter angezeigt,\n"
                "wobei die Schriftfarbe von der Bedeutung des Wortes abweicht. Der User muss schnell erkennen,\n"
                "wenn das Wort und die Schriftfarbe übereinstimmen, und daraufhin klicken.\n"
                "Durch die fortlaufende Anzeige von richtigen und falschen Antworten sowie\n"
                "eine Streak-Anzeige wird die kognitive Leistung des Users bewertet.\n"
                "Die schnelle Anpassung an unerwartete Situationen und die Fähigkeit,\n"
                "zwischen verschiedenen Reizen zu unterscheiden, sind wesentliche Fähigkeiten\n"
                "für den Einsatz von Polizei- und Feuerwehrkräften.";
        _gameRules = "Auf dem Bildschirm werden zuerst Wörter in unterschiedlicher Farbe angezeigt.\n"
                     "Diese sind in Reihenfolge anhand des Wortes nicht der Farbe zuzuordnen.\n"
                     "Anschließend gibt es eine ähnliche Aufgabe nur muss man nun die Farbe des Wortes den Wörter unterhalb zuordnen\n";
        _gameControls = "Linke Maustaste: Klicken der richtigen Antworten in der richting Reihenfolge";
    }

    void ColorMatch::render() {
        ui_elements::InfoBox(_showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
            start();
        }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endboxTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endboxText));

            ui_elements::Centered([this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    start();
                }

                if (ImGui::Button("Zurück zur Startseite")) {
                    scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
                }
            });
        });

        if (_isGameRunning) {
            renderGame();
        }
    }

    void ColorMatch::renderGame() {
        ui_elements::Window("Color Match Game").render([this] {
            _timer.render();

            if (_timer.isExpiredNow()) {
                _isGameRunning = false;
                _showEndbox = true;
                _endboxTitle = "Zeit abgelaufen!";
                static std::string endboxString{
                        "Richtige: " + std::to_string(_numberOfCorrectClicksInTotal) + "\nLängster Streak: " +
                        std::to_string(_numberOfCorrectClicksSinceLastError)};
                _endboxText = (endboxString).c_str();
            }
            if (_isTimeForNewRandomColors) {
                pickRandomColorsText();
                pickRandomColorsImVec4();
                _isTimeForNewRandomColors = false;
            }
            ui_elements::Centered([this] {
                displayRandomColors();
                displayColorButtons();
            });
        });
    }

    void ColorMatch::start() {
        _isGameRunning = true;
        _showEndbox = false;
        _timer.start();
    }

    void ColorMatch::reset() {
        _isGameRunning = false;

        _isTimeForNewRandomColors = true;
        _indexOfCurrentColor = 0;
        _numberOfCorrectClicksInTotal = 0;
        _numberOfCorrectClicksSinceLastError = 0;
    }

    void ColorMatch::pickRandomColorsText() {
        _randomColorsText.clear();
        for (int i{0}; i < _numberOfRandomColors; i++) {
            _randomColorsText.emplace_back(commons::RandomPicker::pickRandomElement(_AVAILABLE_COLORS_TEXT));
        }
    }

    void ColorMatch::pickRandomColorsImVec4() {
        _randomColorsImVec4.clear();
        for (int i{0}; i < _numberOfRandomColors; i++) {
            _randomColorsImVec4.emplace_back(commons::RandomPicker::pickRandomElement(_AVAILABLE_COLORS_IMVEC4));
        }
    }

    void ColorMatch::displayRandomColors() {
        for (int i{0}; i < _randomColorsText.size(); i++) {
            ImGui::PushFont(_indexOfCurrentColor == i ? commons::Fonts::_header2 : commons::Fonts::_header3);
            ImGui::PushStyleColor(ImGuiCol_Text, _randomColorsImVec4.at(i));
            ImGui::Text("%s", _randomColorsText.at(i).c_str());
            ImGui::SameLine();
            ImGui::PopStyleColor();
            ImGui::PopFont();
        }
    }

    void ColorMatch::displayColorButtons() {
        ImGui::NewLine();
        for (int i{0}; i < _AVAILABLE_COLORS_TEXT.size(); i++) {
            if (_indexOfCurrentColor >= _numberOfRandomColors) {
                _isTimeForNewRandomColors = true;
                _indexOfCurrentColor = 0;
            }
            bool isCurrentColor = _AVAILABLE_COLORS_TEXT.at(i) == _randomColorsText.at(_indexOfCurrentColor);
            ImGui::PushStyleColor(ImGuiCol_Button, _AVAILABLE_COLORS_IMVEC4.at(i)); // Normal state
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _AVAILABLE_COLORS_IMVEC4.at(i)); // Hover state
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                  isCurrentColor ? commons::ColorTheme::SUCCESS_COLOR
                                                 : commons::ColorTheme::ERROR_COLOR);

            std::string buttonID = "##" + _AVAILABLE_COLORS_TEXT.at(i);
            if (ImGui::Button(buttonID.c_str(), ImVec2(70, 30))) {

                if (isCurrentColor) {
                    _indexOfCurrentColor++;
                    _numberOfCorrectClicksInTotal++;
                    _numberOfCorrectClicksSinceLastError++;
                } else {
                    _numberOfCorrectClicksSinceLastError = 0;
                    _timer.reduceTime(5);
                };
            }
            ImGui::PopStyleColor(3);
            ImGui::SameLine();
        }
    }

    void ColorMatch::updateStatistics() {
        // add code here
    }

}






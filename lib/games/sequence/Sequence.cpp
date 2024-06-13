#include "Sequence.hpp"
#include "Fonts.hpp"
#include "ColorTheme.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "TextCentered.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "Window.hpp"
#include "Centered.hpp"
#include <iostream>
#include <random>
#include <thread>

namespace sequence {

    Sequence::Sequence() : Game(abstract_game::GameID::SEQUENCE) {
        _gameName = "Abfolge-Merken-Spiel";
        _gameDescription = "Unser Abfolge-Merken-Spiel soll die Fähigkeit testen, sich Abfolgen einzuprägen und korrekt wiederzugeben.\n";
        _gameRules = "Auf dem Bildschirm werden 9 verschiedene Buttons angezeigt.\n"
                     "Diese Buttons werden nacheinander aufleuchten und anschließend müssen die Buttons in exakt dieser\n"
                     "Reihenfolge angeklickt werden. Die Abfolge muss also wiederholt werden.\n"
                     "Die Abfolge wird schrittweise ausgegeben. Also erst nur ein Button, dann zwei, dann drei usw.\n"
                     "bis zu maximal 20 Buttons in einer Abfolge.\n";
        _gameControls = "Linke Maustaste: Klicken der Buttons in der korrekten Reihenfolge.\n";

        _buttonStates.resize(_NUMBER_OF_BUTTONS, false);
    }

    void Sequence::render() {
        ui_elements::InfoBox(_gameID, _showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
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

    void Sequence::renderGame() {
        ui_elements::Window("Sequence Game").render(([this] {

            ui_elements::Centered([this] {
                ImGui::Text("Wiederhole die Reihenfolge!");
                ImGui::NewLine();

                displayButtons();
            });
        }));

    }

    void Sequence::start() {
        reset();
        _isGameRunning = true;
        _showEndbox = false;
        chooseNextRandomButton();

        showSequence();
    }

    void Sequence::reset() {
        _levelCounter = 1;
        _buttonsClickedSequence.clear();
        std::fill(_buttonStates.begin(), _buttonStates.end(), false); //Set all button states to false (not lighting up)
    }

    void Sequence::stop() {
        _endBoxString = "Du hast eine Abfolge von " + std::to_string(_longestReproducedSequence) +
                        " Klicks richtig wiederholt!";
        _endboxText = _endBoxString.c_str();
        _isGameRunning = false;
        _showEndbox = true;
        _endboxTitle = "Falsch geklickt!";
    }

    void Sequence::updateStatistics() {

    }

    void Sequence::displayButtons() {
        ImGui::NewLine();
        for (int i{1}; i <= _NUMBER_OF_BUTTONS; i++) {
            if ((i - 1) % 3) {
                ImGui::SameLine();
            } else {
                ImGui::NewLine();
            }
            if (_buttonStates[i]) {
                std::cout << "Light up this shit " << i << std::endl;
                ImGui::PushStyleColor(ImGuiCol_Button, commons::ColorTheme::ACCENT_COLOR);
            } else {
                std::cout << "No light up :(" << i << std::endl;
                ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::SEAFOAM);
            }

            if (ImGui::Button(std::to_string(i).c_str(), ImVec2(200, 200))) {
                std::cout << "Clicked Button " << i << std::endl;
                isClickedInCorrectOrder();
                start();
            }
            ImGui::PopStyleColor();
        }

    }

    void Sequence::isClickedInCorrectOrder() {


    }

    /**
     * Generates a random number in the range of 1 to 9 to choose a next button to light up for the random sequence.
     */
    void Sequence::chooseNextRandomButton() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(1, _NUMBER_OF_BUTTONS);

        _buttonsClickedSequence.emplace_back(distribution(gen));
    }

    void Sequence::showSequence() {
        for (int button: _buttonsClickedSequence) {
            _buttonStates[button - 1] = true;
            std::cout << "Light up!" << button - 1 << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            _buttonStates[button - 1] = false;
            std::cout << "Wait next light up!" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
} // sequence
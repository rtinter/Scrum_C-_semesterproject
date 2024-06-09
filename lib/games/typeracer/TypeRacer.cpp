#include "TypeRacer.h"
#include "TextCenteredVertically.h"

#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <iostream>

namespace typeracer {
    TypeRacer::TypeRacer() {
        _gameName = "Type Racer";
        _gameDescription = "";
        _gameRules = "";
        _gameControls = "";
    }

    void TypeRacer::render() {
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

    void TypeRacer::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ui_elements::Window("Type Racer").render([this]() {
            std::string sentence = "Das ist ein Test Satz";
            static char input[256] {""};

            // Start time when typing begins
            if (!_run_timer && strlen(input) > 0) {
                _startPoint = std::chrono::steady_clock::now();
                _run_timer = true;
            }
            // Render the sentence with character matching
            for (int i {0}; i < sentence.size(); ++i) {
                if (i < strlen(input) && input[i] == sentence[i]) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::GREEN); // Green
                    if(this->_mistakes > 0) {
                        this->_mistakes--;
                    }
                } else if (i < strlen(input)) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::RED); // Red
                    this->_mistakes++;
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text)); // Default
                }

                ImGui::TextUnformatted(std::string(1, sentence[i]).c_str());
                ImGui::PopStyleColor();

                ImGui::SameLine(0.0f, 0.0f);

            }

            // Render the input field beneath the sentence
            ImGui::NewLine();
            ImGui::InputText("##hidden_label", input, IM_ARRAYSIZE(input));

            // Calculate WPM in real-time
            if (_run_timer && strlen(input) > 0) {
                auto currentTime = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsedSeconds = currentTime - _startPoint;
                float minutes = elapsedSeconds.count() / 60.0f;
                int numChars = strlen(input);
                _wpm = (numChars / 5.0f) / minutes;

                // Stop and save the WPM when the sentence is completed
                if (this->_mistakes == 0 && strlen(input) >= sentence.size()) {
                    _run_timer = false;
                    _isGameRunning = false;
                    _showEndbox = true;
                }
            }

            // Display WPM
            ImGui::Text("Words per minute (WPM): %.2f", _wpm);
        });
        ImGui::PopStyleColor();
    }

    void TypeRacer::start() {
        _isGameRunning = true;
        std::cout << _isGameRunning << std::endl;
        _showEndbox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void TypeRacer::stop() {
        _isGameRunning = false;
    }

    void TypeRacer::reset() {
        _isGameRunning = false;
        _showEndbox = false;
        _mistakes = 0;
        _wpm = 0.0f;
    }

    void TypeRacer::updateStatistics() {

    }

    std::string TypeRacer::getName() const {
        return _gameName;
    }
} // typeracer
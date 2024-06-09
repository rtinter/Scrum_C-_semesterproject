#include "TypeRacer.hpp"

#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>

namespace typeracer {
    TypeRacer::TypeRacer() {
        _gameName = "Type Racer";
        _gameDescription = "";
        _gameRules = "";
        _gameControls = "";
    }

    std::string TypeRacer::_endBoxTextString {};

    void TypeRacer::render() {
        ui_elements::InfoBox(_showInfobox,
        _gameName,
        _gameDescription,
        _gameRules,
        _gameControls,
        [this] (){
            reset();
        }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endboxTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endboxText));

            ui_elements::Centered([this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    // Abspeichern von stuff
                    reset();
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

            // Start time when typing begins
            if (!_runTimer && strlen(_input) > 0) {
                _startPoint = std::chrono::steady_clock::now();
                _runTimer = true;
            }
            // Render the sentence with character matching
            for (int i {0}; i < sentence.size(); ++i) {
                if (i < strlen(_input) && _input[i] == sentence[i]) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::GREEN); // Green
                    if(_mistakes > 0) {
                        _mistakes--;
                    }
                } else if (i < strlen(_input)) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::RED); // Red
                    _mistakes++;
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text)); // Default
                }

                ImGui::TextUnformatted(std::string(1, sentence[i]).c_str());
                ImGui::PopStyleColor();

                ImGui::SameLine(0.0f, 0.0f);

            }

            // Render the _input field beneath the sentence
            ImGui::NewLine();
            ImGui::InputText("##hidden_label", _input, IM_ARRAYSIZE(_input));

            // Calculate WPM in real-time
            if (_runTimer && strlen(_input) > 0) {
                auto currentTime = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsedSeconds = currentTime - _startPoint;
                float minutes = elapsedSeconds.count() / 60.0f;
                int numChars = strlen(_input);
                _wpm = (numChars / 5.0f) / minutes;

                std::string wpmString = std::to_string(_wpm);
                // Stop and save the WPM when the sentence is completed
                if (strlen(_input) >= sentence.size() && _mistakes == 0) {
                    _endBoxTextString =
                            "Wörter pro Minute: " + wpmString + " WPM";
                    _endboxText = _endBoxTextString.c_str();
                    _runTimer = false;
                    _isGameRunning = false;
                    _showEndbox = true;
                }
            }

            // Display WPM
            ImGui::Text("Wörter pro Minute (WPM): %.2f", _wpm);
        });
        ImGui::PopStyleColor();
    }

    void TypeRacer::start() {
        _isGameRunning = true;
        _showEndbox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void TypeRacer::stop() {
        _isGameRunning = false;
    }

    void TypeRacer::reset() {
        _mistakes = 0;
        _wpm = 0.0f;
        _endBoxTextString = "";
        for (char & i : _input) {
            i = '\0';
        }
        start();
    }

    void TypeRacer::updateStatistics() {

    }

    std::string TypeRacer::getName() const {
        return _gameName;
    }

    TypeRacer::~TypeRacer() {
        _mistakes = 0;
        _wpm = 0.0f;
        _runTimer = false;
        for (char & i : _input) {
            i = '\0';
        }
    }
} // typeracer
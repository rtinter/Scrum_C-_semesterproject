#include "TypeRacer.hpp"

#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <random>
#include <set>
#include <sstream>
#include <iomanip>
#include "fireDepartmentAndPoliceTexts.h"
#include "GameSessionManager.hpp"


namespace typeracer {
    TypeRacer::TypeRacer() : abstract_game::Game(abstract_game::GameID::TYPERACER) {
        _gameName = "Type Racer";
        _gameDescription =
                "TypeRacer ist ein spannendes Tipp-Spiel, das deine Tippgeschwindigkeit und Genauigkeit herausfordert.\n"
                "Das Spiel wird auf Englisch gespielt, um deine Englischkenntnisse zu verbessern.\n"
                "Bei der Polizei und Feuerwehr ist wichtig, dass die Kommunikation schnell und präzise ist.\n"
                "Beispielsweise könnten Berichte auch auf Englisch verfasst werden, \n um den Austausch mit Menschen aus anderen Ländern zu erleichtern.\n"
                "Viel Spaß beim Tippen!\n";


        _gameRules =
                "1. Das Spiel zeigt dir einen zufälligen Satz zu dem Thema Feuerwehr und Polizei an.\n"
                "2. Deine Tippgeschwindigkeit wird in Wörtern pro Minute (WPM) gemessen.\n"
                "3. Das Spiel endet, wenn du den gesamten Satz korrekt getippt hast.\n"
                "4. Falsch getippte Zeichen werden rot hervorgehoben. Korrekte Zeichen werden grün hervorgehoben.\n"
                "5. Deine endgültige WPM-Wertung wird angezeigt, sobald du den Text beendet hast.";

        _gameControls =
                "Steuerung:\n"
                "1. Tippe die Zeichen des angegebenen Satzes in das Eingabefeld.\n"
                "2. Verwende die Rücktaste, um Fehler zu korrigieren.\n"
                "3. Deine Eingabe wird beendet, wenn du alle Wörter richtig geschrieben hast.\n"
                "4. Klicke auf 'Versuch es nochmal', um das Spiel zurückzusetzen und einen neuen Satz zu erhalten.\n"
                "5. Klicke auf 'Zurück zur Startseite', um zum Hauptmenü zurückzukehren.";
    }


    std::string TypeRacer::_endBoxTitleString{};
    std::string TypeRacer::_endBoxTextString{};

    int getRandomIndex(int arraySize) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, arraySize - 1);

        int randomIndex = distr(gen);
        return randomIndex;
    }

    void TypeRacer::render() {
        ui_elements::InfoBox(
                _gameID,
                _showInfobox,
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this]() {
                    reset();
                    _randomIndex = getRandomIndex(FireDepartmentAndPoliceTexts::_mixedTexts.size());
                    _startGameSession = std::chrono::steady_clock::now();
                }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::Spacing();
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endboxTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endboxText));
            ui_elements::Centered(true, true,[this]() {
                if (ImGui::Button("Versuch es nochmal")) {
                    reset();
                    _randomIndex = getRandomIndex(FireDepartmentAndPoliceTexts::_mixedTexts.size());
                }
                if (ImGui::Button("Zurück zur Startseite")) {
                    abstract_game::GameSessionManager::getInstance().endSession(); // End the session when going back
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
            std::set<int> mistypedIndices;
            std::string sentence = FireDepartmentAndPoliceTexts::_mixedTexts[_randomIndex];
            // for testing purposes
            // std::string sentence = "Dies ist ein Test.";
            float windowWidth = ImGui::GetWindowWidth();
            float textWidth = ImGui::CalcTextSize(sentence.c_str()).x;

            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();

            // Start time when typing begins
            if (!_runTimer && strlen(_input) > 0) {
                _startPoint = std::chrono::steady_clock::now();
                _runTimer = true;
            }
            ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
            // Render the sentence with character matching
            for (int i{0}; i < sentence.size(); ++i) {
                if (i < strlen(_input) && _input[i] == sentence[i]) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::GREEN); // Green
                    mistypedIndices.erase(i);
                } else if (i < strlen(_input)) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::RED); // Red
                    mistypedIndices.insert(i);
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text)); // Default
                }

                ImGui::PushFont(commons::Fonts::_header2);
                ImGui::TextUnformatted(std::string(1, sentence[i]).c_str());
                ImGui::PopFont();
                ImGui::PopStyleColor();

                if (sentence[i] == '.') {
                    ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
                    ImGui::NewLine();
                    ImGui::SetCursorPosX((windowWidth - textWidth) / 2);
                    i++;
                }
                ImGui::SameLine(0.0f, 0.0f);


            }

            // Render the _input field beneath the sentence
            ImGui::NewLine();

            ImGui::SetCursorPosX((windowWidth - textWidth) / 2);

            ImGui::PushItemWidth(windowWidth / 2);
            ImGui::PushFont(commons::Fonts::_header2);
            ImGui::InputText("##hidden_label", _input, IM_ARRAYSIZE(_input));
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();
            // Display WPM
            ImGui::Text("%.2f wpm", _wpm);

            // Calculate WPM in real-time
            if (_runTimer && strlen(_input) > 0) {
                auto currentTime = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsedSeconds = currentTime - _startPoint;
                float minutes = elapsedSeconds.count() / 60.0f;
                int numChars = strlen(_input);
                _wpm = (numChars / 5.0f) / minutes;

                std::stringstream wpmStream;
                wpmStream << std::setprecision(4) << _wpm;


                // Stop and save the WPM when the sentence is completed
                if (strlen(_input) >= sentence.size() && mistypedIndices.empty()) {
                    _endBoxTitleString = "Geschafft!";
                    _endboxTitle = _endBoxTitleString.c_str();
                    _endBoxTextString =
                            "Wörter pro Minute: " + wpmStream.str() + " WPM";
                    _endboxText = _endBoxTextString.c_str();
                    _runTimer = false;
                    _isGameRunning = false;
                    _showEndbox = true;
                    _wpmHistory.emplace_back(_wpm);
                }
            }
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
        for (char &i: _input) {
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
        for (char &i: _input) {
            i = '\0';
        }
    }
} // typeracer
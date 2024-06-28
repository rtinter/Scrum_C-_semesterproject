#include "TypeRacer.hpp"

#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <sstream>
#include <iomanip>
#include "fireDepartmentAndPoliceTexts.hpp"
#include "GameSessionManager.hpp"
#include "RandomPicker.hpp"


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

    void TypeRacer::render() {
        ui_elements::InfoBox(
                _gameID,
                _showStartBox,
                "Startbox",
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this]() {
                    reset();
                    _randomIndex = commons::RandomPicker::randomInt(0,FireDepartmentAndPoliceTexts::_mixedTexts.size());
                }).render();

        ui_elements::InfoBox(
                _gameID,
                _showEndBox,
                "Endbox",
                _endBoxTitle,
                _endBoxText,
                [this]() {
                    reset();
                }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void TypeRacer::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ui_elements::Window("Type Racer").render([this]() {
            _windowWidth = ImGui::GetWindowWidth();
            _textWidth = ImGui::CalcTextSize(_sentence.c_str()).x;

            // For testing purposes comment out the desired _sentence and uncomment the other _sentence
            // Get a random sentence from the list
            _sentence = FireDepartmentAndPoliceTexts::_mixedTexts[_randomIndex];
            //_sentence= "Dies ist ein Test.";

            // for spacing to the top of the window
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();
            ImGui::NewLine();

            /*********************************
            *  start Timer for calculating WPM
            ***********************************/
            if (!_runTimer && strlen(_input) > 0) {
                _startPoint = std::chrono::steady_clock::now();
                _runTimer = true;
            }

            ImGui::SetCursorPosX((_windowWidth - _textWidth) / 2);

            /*********************************
            *  Display the sentence
             *  Highlight correct and incorrect characters
             *  in green and red respectively
             *  and display the _input field beneath the sentence
            ***********************************/
            for (int i{0}; i < _sentence.size(); ++i) {
                if (i < strlen(_input) && _input[i] == _sentence[i]) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::GREEN); // correct character in green
                    // erase the index from the set if the character is typed correctly
                    _mistypedIndices.erase(i);
                } else if (i < strlen(_input)) {
                    ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::RED); // incorrect character in red
                    // add the index to the set if the character is typed incorrectly
                    _mistypedIndices.insert(i);
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetStyleColorVec4(ImGuiCol_Text)); // Default
                }

                ImGui::PushFont(commons::Fonts::_header2);
                ImGui::TextUnformatted(std::string(1, _sentence[i]).c_str());
                ImGui::PopFont();
                ImGui::PopStyleColor();

                if (_sentence[i] == '.') {
                    ImGui::SetCursorPosX((_windowWidth - _textWidth) / 2);
                    ImGui::NewLine();
                    ImGui::SetCursorPosX((_windowWidth - _textWidth) / 2);
                    i++;
                }
                ImGui::SameLine(0.0f, 0.0f);


            }

            // Render the _input field beneath the sentence
            ImGui::NewLine();

            ImGui::SetCursorPosX((_windowWidth - _textWidth) / 2);

            ImGui::PushItemWidth(_windowWidth / 2);
            ImGui::PushFont(commons::Fonts::_header2);
            ImGui::InputText("##hidden_label", _input, IM_ARRAYSIZE(_input));
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();

            ImGui::Text("%.2f wpm", _wpm);

            /*********************************
            *  calculate WPM in real time
             *  stop the timer when the sentence is completed and save the WPM
            ***********************************/
            if (_runTimer && strlen(_input) > 0) {
                auto currentTime{std::chrono::steady_clock::now()};
                std::chrono::duration<float> elapsedSeconds{currentTime - _startPoint};
                float minutes{elapsedSeconds.count() / 60.0f};
                int numChars = strlen(_input);
                _wpm = (numChars / 5.0f) / minutes;

                std::stringstream wpmStream;
                wpmStream << std::setprecision(4) << _wpm;

                if (strlen(_input) >= _sentence.size() && _mistypedIndices.empty()) {
                    _endBoxText =
                            "Wörter pro Minute: " + wpmStream.str() + " WPM";
                    stop();
                }
            }
        });
        ImGui::PopStyleColor();
    }

    void TypeRacer::start() {
        _isGameRunning = true;
        _showEndBox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void TypeRacer::stop() {
        _endBoxTitle = "Geschafft!";
        _runTimer = false;
        _showEndBox = true;
        updateStatistics();
        _isGameRunning = false;
    }

    void TypeRacer::reset() {
        _wpm = 0.0f;
        _endBoxText = "";

        for (char &i : _input) {
            i = '\0';
        }

        _randomIndex = 0;
        _sentence.clear();
        _mistypedIndices.clear();
        _runTimer = false;
        _startPoint = std::chrono::steady_clock::time_point();

        start();
    }

    void TypeRacer::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Wörter pro Minute",
                                                                                     _wpm);
    }

    std::string TypeRacer::getName() const {
        return _gameName;
    }

    TypeRacer::~TypeRacer() {
        _wpm = 0.0f;
        _runTimer = false;
        for (char &i : _input) {
            i = '\0';
        }
        _randomIndex = 0;
        _sentence.clear();
        _mistypedIndices.clear();
    }
} // typeracer
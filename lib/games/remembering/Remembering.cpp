#include "Remembering.hpp"
#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <sstream>
#include <algorithm>

namespace games {

    Remembering::Remembering() : Game(abstract_game::GameID::REMEMBERING) {
        _gameName = "Remembering";
        _gameDescription =
                "Unser Merkspiel bewertet die Fähigkeit, sich schnell und präzise Fakten zu merken,\n"
                "was für Polizei- und Feuerwehrarbeit unerlässlich ist.\n"
                "In diesen Berufen ist es entscheidend, rasch und genau auf Informationen zu reagieren,\n"
                "daher ist das Spiel ein zuverlässiger Indikator für das persönliche können und hilft \n"
                "sich in dieser Domäne zu verbessern.";
        _gameRules = "Ein Text wird angezeigt, der eine Zeugenaussage oder andere detaillierte Informationen enthält.\n"
                     "Der User hat 30 Sekunden Zeit, sich den Text durchzulesen und so viele Details wie möglich zu merken.\n"
                     "Nach Ablauf der Zeit verschwindet der Text und es werden Detailfragen zum jeweiligen Text gestellt.\n"
                     "Versuche, so viele Fragen wie möglich richtig zu beantworten!"
                     "Beachte die Rechtschreibung und schreibe zahlen aus ";
        _gameControls = "Linke Maustaste um das Feld in das du schreiben möchtest auszuwählen\n"
                        "Tastatur um deine Antwort einzugeben.";

        initializeQuestionsAndAnswers(); // Initialize the questions and answers
        _timer.start();
    }

    void Remembering::initializeQuestionsAndAnswers() {
        questions = {
                {"In welchem Monat fand das Ereignis statt?", {"Januar",          "Mai",             "Juni",        "Dezember"},   2},
                {"Um wieviel Uhr fand das Ereignis statt?",   {"13:00",           "14:30",           "15:00",       "16:30"},      1},
                {"In welchem Café saß die Person?",           {"Bäckerei",        "Kaffeekränzchen", "Restaurant",  "Bar"},        1},
                {"In welcher Straße liegt das Café?",         {"Bahnhofstraße",   "Hauptstraße",     "Nebenstraße", "Ringstraße"}, 1},
                {"Welches Geräusch hörte die Person?",        {"Schrei",          "Sirene",          "Glas",        "Motor"},      2},
                {"Was trug die Person?",                      {"Kapuzenpullover", "Anzug",           "T-Shirt",     "Hemd"},       0},
                {"Welche Farbe hatte die Jeans der Person?",  {"schwarz",         "rot",             "blau",        "weiß"},       2},
                {"Wie groß war die Person?",                  {"1,60",            "1,70",            "1,80",        "1,90"},       2},
                {"In welche Richtung rannte die Person?",     {"Bahnhof",         "Stadtpark",       "Marktplatz",  "Kirche"},     1},
                {"Wie heißt der Polizist?",                   {"Schmidt",         "Müller",          "Weber",       "Fischer"},    1},
                {"Wie viel ist das Diamantarmband wert?",     {"5.000",           "10.000",          "15.000",      "20.000"},     1},
                {"Wie viel ist die Rolex-Uhr wert?",          {"10.000",          "15.000",          "20.000",      "25.000"},     1},
                {"Welches Auto fuhr der Täter?",              {"BMW",             "Mercedes",        "Audi",        "Volkswagen"}, 2},
                {"Welches Kennzeichen hatte das Auto?",       {"B-CD 1234",       "B-AB 1234",       "B-EF 5678",   "B-GH 9012"},  1},
                {"Wartete noch jemand im Auto?",              {"ja",              "nein",            "vielleicht",  "unbekannt"},  0}
        };
    }

    void Remembering::render() {
        ui_elements::InfoBox(_gameID, _showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
            start();
        }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(std::move(_endboxTitle));
            ImGui::PopFont();
            ui_elements::TextCentered(std::move(_endboxText));

            ui_elements::Centered(true, true, [this]() {
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


    void Remembering::renderGame() {
        ui_elements::Window("Remembering Game").render([this]() {
            if (showText) {
                _timer.render();
                displayCenteredText(getText().c_str());
            }
            if (_timer.isExpiredNow()) {
                showText = false;
            }
            if (!showText) {
                static int selectedAnswers[15] = {-1};
                static bool submitted = false;

                for (int i = 0; i < questions.size(); ++i) {
                    const auto &q = questions[i];
                    ImGui::Text("%s", q.question.c_str()); // Display the question

                    // Convert std::vector<std::string> to const char* array
                    std::vector<const char *> answers_cstr;
                    for (const auto &answer: q.answers) {
                        answers_cstr.push_back(answer.c_str());
                    }

                    if (submitted) {
                        // Display the question with a color based on the correctness of the answer
                        ImVec4 color = (selectedAnswers[i] == q.correctAnswerIndex) ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0,
                                                                                                                  0,
                                                                                                                  1);
                        ImGui::PushStyleColor(ImGuiCol_Text, color);
                        ImGui::Combo(("##combo" + std::to_string(i)).c_str(), &selectedAnswers[i], answers_cstr.data(),
                                     answers_cstr.size());
                        ImGui::PopStyleColor();
                    } else {
                        ImGui::Combo(("##combo" + std::to_string(i)).c_str(), &selectedAnswers[i], answers_cstr.data(),
                                     answers_cstr.size());
                    }
                }

                if (!submitted && ImGui::Button("Submit All")) {
                    submitted = true;
                }
            }
        });
    }

    std::string Remembering::getText() const {
        return text;
    }

    void Remembering::displayCenteredText(const char *text) const {
        ImVec2 windowSize = ImGui::GetWindowSize();

        // Split the text into lines
        std::istringstream stream(text);
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(stream, line)) {
            lines.push_back(line);
        }

        // Display each line centered
        for (const auto &line: lines) {
            ImVec2 textSize = ImGui::CalcTextSize(line.c_str(), nullptr, false, windowSize.x);
            float offsetX = (windowSize.x - textSize.x) * 0.5f;

            if (offsetX > 0) {
                ImGui::SetCursorPosX(offsetX);
            } else {
                ImGui::SetCursorPosX(0);
            }

            ImGui::TextWrapped("%s", line.c_str());
        }
    }

    void Remembering::start() {
        reset();
        _isGameRunning = true;
        _showEndbox = false;
    }

    void Remembering::stop() {
        _isGameRunning = false;
    }

    void Remembering::reset() {
        std::fill(_userTextBuffer.begin(), _userTextBuffer.end(), 0);
    }

    void Remembering::updateStatistics() {
        // add code here
    }
}
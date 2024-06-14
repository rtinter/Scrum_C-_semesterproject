#include "Remembering.hpp"

namespace games {

    std::string Remembering::_endBoxTitleString{};
    std::string Remembering::_endBoxTextString{};
    std::vector<int> Remembering::selectedAnswers;

    Remembering::Remembering() : Game(abstract_game::GameID::REMEMBERING),
                                 questionBank(std::make_unique<QuestionBank>()) {
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

        selectRandomQuestionSet();
        selectedAnswers.resize(currentQuestionSet.questions.size(), -1);
        _timer.start();
    }

    void Remembering::selectRandomQuestionSet() {
        currentQuestionSet = questionBank->getRandomQuestionSet();
    }

    void Remembering::render() {
        ui_elements::InfoBox(_gameID, _showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
            start();
        }).render();

        ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered(_endBoxTitleString.c_str());
            ImGui::PopFont();

            for (int i{0}; i < 5; ++i) {
                ImGui::Spacing();
            }

            displayCenteredText(_endBoxTextString);

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
                displayCenteredText(currentQuestionSet.text.c_str());
            }
            if (_timer.isExpiredNow()) {
                showText = false;
            }
            if (!showText) {
                setStyles();

                for (int i = 0; i < currentQuestionSet.questions.size(); ++i) {
                    renderQuestion(i, currentQuestionSet.questions[i], selectedAnswers[i]);
                }

                ImGui::PopStyleColor(2);

                renderSubmitButtons();
            }
        });
    }

    void Remembering::renderQuestion(int index, const QuestionBank::Question &q, int &selectedAnswer) {
        // Calculate text width
        ImVec2 textSize = ImGui::CalcTextSize(q.question.c_str());
        float textOffsetX = (ImGui::GetWindowWidth() - textSize.x) / 2.0f;

        // Calculate combo box width and offset
        float comboWidth = ImGui::GetWindowWidth() * 0.3f;
        float comboOffsetX = (ImGui::GetWindowWidth() - comboWidth) / 2.0f;

        // Set cursor position for text
        ImGui::SetCursorPosX(textOffsetX);
        ImGui::Text("%s", q.question.c_str()); // Display the question

        std::vector<const char *> answers;
        for (const auto &answer: q.answers) {
            answers.emplace_back(answer.c_str());
        }

        // Set cursor position for combo box
        ImGui::SetCursorPosX(comboOffsetX);
        ImGui::SetNextItemWidth(comboWidth);

        if (submitted) {
            // Determine the color based on correctness and whether an answer was selected
            ImVec4 color;
            if (selectedAnswer == -1) {
                color = ImVec4(1, 0, 0, 1); // Red for unanswered
            } else {
                color = (selectedAnswer == q.correctAnswerIndex) ?
                        ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1); // Green for correct, red for incorrect
            }

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            (void) ImGui::Combo(("##combo" + std::to_string(index)).c_str(), &selectedAnswer,
                                answers.data(), answers.size());
            ImGui::PopStyleColor();
        } else {
            (void) ImGui::Combo(("##combo" + std::to_string(index)).c_str(), &selectedAnswer,
                                answers.data(), answers.size());
        }
    }

    void Remembering::setStyles() {
        // Set style for combo boxes
        ImGuiStyle &style = ImGui::GetStyle();
        style.ItemSpacing = ImVec2(12, 4);
        style.FramePadding = ImVec2(4, 2);

        // Set color scheme for the combo box
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                              ImVec4(0.4f, 0.4f, 0.4f, 1.0f)); // Active background color
        ImGui::PushStyleColor(ImGuiCol_PopupBg,
                              ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Popup background color (light gray)
    }

    void Remembering::renderSubmitButtons() {
        ui_elements::Centered(true, false, [this]() {
            if (!submitted && ImGui::Button("Submit All")) {
                submitted = true;
                _showContinueButton = true; // Zeige den Button nach dem Einreichen
            }

            if (_showContinueButton && ImGui::Button("Weiter zur Auswertung")) {
                submitted = false;
                _showContinueButton = false;
                _showEndbox = true;
                // Calculate the final score and prepare the end box text
                for (int i = 0; i < currentQuestionSet.questions.size(); ++i) {
                    if (selectedAnswers[i] == currentQuestionSet.questions[i].correctAnswerIndex) {
                        ++score;
                    }
                }

                _endBoxTitleString = "Dein Ergebnis";
                _endBoxTextString = displayEvaluation(score, currentQuestionSet.questions.size());
                displayCenteredText(_endBoxTextString.c_str());
            }
        });
    }

    std::string Remembering::displayEvaluation(int const &score, int const &size) const {
        std::string evaluation =
                std::to_string(score) + " von " + std::to_string(size) + " richtig.\n";
        if (score >= (3 * size) / 4) {
            evaluation += "Sehr gut gemacht!\n\n";
        } else if (score >= size / 2) {
            evaluation += "Gut gemacht!\n\n";
        } else {
            evaluation += "Satz mit X das war wohl nix. Nächstes mal wird besser!\n\n";
        }
        return evaluation;
    }

    std::string Remembering::getText() const {
        return currentQuestionSet.text;
    }

    void Remembering::displayCenteredText(std::string const &text) const {
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
        showText = true;
        _timer.reset();
        _timer.start();
    }

    void Remembering::stop() {
        _isGameRunning = false;
    }

    void Remembering::reset() {
        selectRandomQuestionSet();
        selectedAnswers.assign(currentQuestionSet.questions.size(), -1); // Zurücksetzen der ausgewählten Antworten
        submitted = false;
        score = 0;
        std::fill(_userTextBuffer.begin(), _userTextBuffer.end(), 0);
    }

    void Remembering::updateStatistics() {
        // add code here
    }
}

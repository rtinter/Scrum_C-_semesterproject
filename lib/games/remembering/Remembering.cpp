#include "Remembering.hpp"
#include "SoundPolice.hpp"
#include "Sound.hpp"

namespace games {

    std::vector<int> Remembering::_selectedAnswers;

    Remembering::Remembering() : Game(abstract_game::GameID::REMEMBERING),
                                 _questionBank(std::make_unique<QuestionBank>()) {
        _gameName = "Remembering";
        _gameDescription =
                "Unser Merkspiel bewertet die Fähigkeit, sich schnell und präzise Fakten zu merken,\n"
                "was für Polizei- und Feuerwehrarbeit unerlässlich ist.\n"
                "In diesen Berufen ist es entscheidend, rasch und genau auf Informationen zu reagieren,\n"
                "daher ist das Spiel ein zuverlässiger Indikator für das persönliche können und hilft \n"
                "sich in dieser Domäne zu verbessern.";
        _gameRules = "Ein Text wird angezeigt, der eine Zeugenaussage \n"
                     "oder andere detaillierte Informationen enthält.\n"
                     "Der User hat 30 Sekunden Zeit, sich den Text durchzulesen und so \n"
                     "viele Details wie möglich zu merken.\n"
                     "Nach Ablauf der Zeit verschwindet der Text und es werden \n"
                     "Detailfragen zum jeweiligen Text gestellt.\n"
                     "Versuche, so viele Fragen wie möglich richtig zu beantworten!\n"
                     "Beachte die Rechtschreibung und schreibe zahlen aus ";
        _gameControls = "Linke Maustaste um das Feld in das du schreiben möchtest auszuwählen\n"
                        "Tastatur um deine Antwort einzugeben.";

        selectRandomQuestionSet();
        _selectedAnswers.resize(_currentQuestionSet.questions.size(), -1);
        _timer.start();
    }

    void Remembering::selectRandomQuestionSet() {
        _currentQuestionSet = _questionBank->getRandomQuestionSet();
    }

    void Remembering::render() {
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();

        ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            reset();
        }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void Remembering::renderGame() {
        ui_elements::Window("Remembering Game").render([this]() {
            if (_showText) {
                _timer.render();
                displayCenteredText(_currentQuestionSet.text.c_str());
            }
            if (_timer.isExpiredNow()) {
                _showText = false;
            }
            if (!_showText) {
                setStyles();

                for (int i = 0; i < _currentQuestionSet.questions.size(); ++i) {
                    renderQuestion(i, _currentQuestionSet.questions[i], _selectedAnswers[i]);
                }

                ImGui::PopStyleColor(2);

                renderSubmitButtons();
            }
        });
    }

    void Remembering::renderQuestion(int index, const QuestionBank::Question &q, int &selectedAnswer) const {
        // Calculate text width
        ImVec2 textSize = ImGui::CalcTextSize(q.question.c_str());
        float textOffsetX = (ImGui::GetWindowWidth() - textSize.x) / 2.0f;

        float comboWidth = ImGui::GetWindowWidth() * 0.3f;
        float comboOffsetX = (ImGui::GetWindowWidth() - comboWidth) / 2.0f;

        ImGui::SetCursorPosX(textOffsetX);
        ImGui::Text("%s", q.question.c_str());

        std::vector<const char *> answers;
        for (const auto &answer: q.answers) {
            answers.emplace_back(answer.c_str());
        }

        ImGui::SetCursorPosX(comboOffsetX);
        ImGui::SetNextItemWidth(comboWidth);

        if (_submitted) {
            ImVec4 color;
            if (selectedAnswer == -1) {
                color = ImVec4(1, 0, 0, 1);
            } else {
                color = (selectedAnswer == q.correctAnswerIndex) ?
                        ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1);
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
        ImGuiStyle &style = ImGui::GetStyle();
        style.ItemSpacing = ImVec2(12, 4);
        style.FramePadding = ImVec2(4, 2);

        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                              ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_PopupBg,
                              ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
    }

    void Remembering::renderSubmitButtons() {
        ui_elements::Centered(true, false, [this]() {
            if (!_submitted && ImGui::Button("Submit All")) {
                _submitted = true;
                _showContinueButton = true;
                commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            }

            if (_showContinueButton && ImGui::Button("Weiter zur Auswertung")) {
                _submitted = false;
                _showContinueButton = false;
                stop();
                for (int i = 0; i < _currentQuestionSet.questions.size(); ++i) {
                    if (_selectedAnswers[i] == _currentQuestionSet.questions[i].correctAnswerIndex) {
                        ++_score;
                    }
                }

                _endBoxTitle = "Dein Ergebnis";
                _endBoxText = displayEvaluation(_score, _currentQuestionSet.questions.size());
                displayCenteredText(_endBoxText);
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

    void Remembering::displayCenteredText(std::string const &text) const {
        ImVec2 windowSize = ImGui::GetWindowSize();

        std::istringstream stream(text);
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(stream, line)) {
            lines.push_back(line);
        }

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
        _isGameRunning = true;
        _showEndBox = false;
        _showText = true;
        _timer.reset();
        _timer.start();
        _selectedAnswers.assign(_currentQuestionSet.questions.size(), -1);
        std::fill(_userTextBuffer.begin(), _userTextBuffer.end(), 0);
    }

    void Remembering::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;
    }

    void Remembering::reset() {
        start();
        selectRandomQuestionSet();
        _selectedAnswers.assign(_currentQuestionSet.questions.size(), -1);
        _submitted = false;
        _score = 0;
        std::fill(_userTextBuffer.begin(), _userTextBuffer.end(), 0);
    }

    void Remembering::updateStatistics() {
        double percentageOfCorrectAnswers{static_cast<double>(_score) / _currentQuestionSet.questions.size() * 100.};
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("% korrekte Antworten",
                                                                                     percentageOfCorrectAnswers);
    }
}

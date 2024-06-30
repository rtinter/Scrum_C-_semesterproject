#include "Remembering.hpp"
#include "SoundPolice.hpp"
#include "WindowConfig.hpp"

namespace games {

    std::vector<int> Remembering::_selectedAnswers{};

    // Constructor: Initializes the Remembering game with a question bank and default settings
    Remembering::Remembering()
            : Game{abstract_game::GameID::REMEMBERING},
              _questionBank{std::make_unique<QuestionBank>()} {
        _gameName = "Remembering";
        _gameDescription =
                "Unser Merkspiel bewertet die Fähigkeit, sich schnell und präzise Fakten zu merken,\n"
                "was für Polizei- und Feuerwehrarbeit unerlässlich ist.\n"
                "In diesen Berufen ist es entscheidend, rasch und genau auf Informationen zu reagieren,\n"
                "daher ist das Spiel ein zuverlässiger Indikator für das persönliche Können und hilft, \n"
                "sich in dieser Domäne zu verbessern.";

        _gameRules =
                "Ein Text wird angezeigt, der eine Zeugenaussage \n"
                "oder andere detaillierte Informationen enthält.\n"
                "Der User hat 30 Sekunden Zeit, sich den Text durchzulesen und sich so \n"
                "viele Details wie möglich zu merken.\n"
                "Nach Ablauf der Zeit verschwindet der Text und es werden \n"
                "Detailfragen zum jeweiligen Text gestellt.\n"
                "Versuche, so viele Fragen wie möglich richtig zu beantworten!\n";

        _gameControls = "Linke Maustaste auf das Antwortfeld, um die Antwortmöglichkeiten zu sehen. \n"
                        "Linke Maustaste, um die passende Antwort auszuwählen.";

        selectRandomQuestionSet();
        _selectedAnswers.resize(_currentQuestionSet.questions.size(), -1);
        _timer.start();
    }

    // Selects a random set of questions from the question bank
    void Remembering::selectRandomQuestionSet() {
        _currentQuestionSet = _questionBank->getRandomQuestionSet();
    }

    // Renders the game UI elements
    void Remembering::render() {
        ui_elements::InfoBox{_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }}.render();

        ui_elements::InfoBox{_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            reset();
        }}.render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    // Renders the main game content
    void Remembering::renderGame() {
        ui_elements::Window{"Remembering Game"}.render([this]() {
            if (_showText) {
                _timer.render();
                displayCenteredText(_currentQuestionSet.text);
            }
            if (_timer.isExpiredNow()) {
                _showText = false;
            }
            if (!_showText) {
                setStyles(); // Apply custom styles for questions

                // Render each question and its options
                for (int i{0}; i < _currentQuestionSet.questions.size(); ++i) {
                    renderQuestion(i, _currentQuestionSet.questions[i], _selectedAnswers[i]);
                }

                ImGui::PopStyleColor(2);

                renderSubmitButtons();
            }
        });
    }

    // Renders a question and its possible answers
    void Remembering::renderQuestion(int const &index, QuestionBank::Question const &q, int &selectedAnswer) const {
        // Calculate text width for centering
        ImVec2 textSize{ImGui::CalcTextSize(q.question.c_str()).x, ImGui::CalcTextSize(q.question.c_str()).y};
        float textOffsetX{(ImGui::GetWindowWidth() - textSize.x) / 2.0F};

        float comboWidth{ImGui::GetWindowWidth() * 0.3F};
        float comboOffsetX{(ImGui::GetWindowWidth() - comboWidth) / 2.0F};

        ImGui::SetCursorPosX(textOffsetX);
        ImGui::Text("%s", q.question.c_str());

        // Store the answers
        std::vector<char const *> answers;
        answers.reserve(q.answers.size());
        for (auto const &answer: q.answers) {
            answers.emplace_back(answer.c_str());
        }

        ImGui::SetCursorPosX(comboOffsetX);
        ImGui::SetNextItemWidth(comboWidth);

        if (_submitted) {
            // Change text color based on answer correctness
            ImVec4 color;
            if (selectedAnswer == -1) {
                color = ImVec4{1, 0, 0, 1}; // red
            } else {
                color = (selectedAnswer == q.correctAnswerIndex) ?
                        ImVec4{0, 1, 0, 1} : ImVec4{1, 0, 0, 1}; // green
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
        ImGuiStyle &style{ImGui::GetStyle()};
        style.ItemSpacing = ImVec2{12, 4};
        style.FramePadding = ImVec2{4, 2};

        // Push style colors for active frame and popup background
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive,
                              ImVec4{0.4f, 0.4f, 0.4f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_PopupBg,
                              ImVec4{0.8f, 0.8f, 0.8f, 1.0f});
    }

    void Remembering::renderSubmitButtons() {
        // Center the submit buttons
        ui_elements::Centered{true, false, [this]() {
            if (!_submitted && ImGui::Button("Submit All")) {
                _submitted = true;
                _showContinueButton = true;
                commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            }

            if (_showContinueButton && ImGui::Button("Weiter zur Auswertung")) {
                _submitted = false;
                _showContinueButton = false;
                for (int i{0}; i < _currentQuestionSet.questions.size(); ++i) {
                    if (_selectedAnswers[i] == _currentQuestionSet.questions[i].correctAnswerIndex) {
                        ++_score;
                    }
                }
                stop();

                //set endBox Texts after the game
                _endBoxTitle = "Dein Ergebnis";
                _endBoxText = displayEvaluation(_score, _currentQuestionSet.questions.size());
                displayCenteredText(_endBoxText);
            }
        }};
    }

    // Displays the evaluation of the player's performance
    std::string Remembering::displayEvaluation(int const &score, int const &size) {
        std::string evaluation{std::to_string(score) + " von " + std::to_string(size) + " richtig.\n"};
        if (score >= (3 * size) / 4) {
            evaluation += "Sehr gut gemacht!\n\n";
        } else if (score >= size / 2) {
            evaluation += "Gut gemacht!\n\n";
        } else {
            evaluation += "Satz mit X das war wohl nix. Nächstes mal wird besser!\n\n";
        }
        return evaluation;
    }

    // Displays centered text by measuring window and colorsizes
    void Remembering::displayCenteredText(std::string const &text) {
        auto const windowWidth{WindowConfig::WINDOW_WIDTH};

        std::istringstream stream{text};
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(stream, line)) {
            lines.push_back(line);
        }

        for (auto const &li: lines) {
            ImVec2 textSize{ImGui::CalcTextSize(li.c_str(), nullptr, false, windowWidth).x,
                            ImGui::CalcTextSize(li.c_str(), nullptr, false, windowWidth).y};
            float const offsetX{(windowWidth - textSize.x) * 0.5f};

            if (offsetX > 0) {
                ImGui::SetCursorPosX(offsetX);
            } else {
                ImGui::SetCursorPosX(0);
            }

            ImGui::TextWrapped("%s", li.c_str());
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
        double percentageOfCorrectAnswers{static_cast<double>(_score) / _currentQuestionSet.questions.size() * 100};
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("% korrekte Antworten",
                                                                                     percentageOfCorrectAnswers);
    }
}

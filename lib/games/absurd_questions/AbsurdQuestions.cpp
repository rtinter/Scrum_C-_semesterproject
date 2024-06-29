#include "AbsurdQuestions.hpp"
#include "nlohmann/json.hpp"
#include "Logger.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace game {

    // Constructor: Initializes the game with name, description, rules, controls, and loads questions
    AbsurdQuestions::AbsurdQuestions() : abstract_game::Game(abstract_game::GameID::ABSURD_QUESTIONS), _selectedOption{false} {
        _gameName = "Absurde Fragen";
        _gameDescription = "Beantworte die absurden Fragen.";
        _gameRules = "1. Lies die angezeigte Frage.\n2. Entscheide, ob die Aussage richtig oder falsch ist.\n"
                     "3. Bestätige deine Auswahl mit dem Button.\n";
        _gameControls = "Linke Maustaste zur Auswahl der Antwort und ebenfalls zum Bestätigen des Buttons";

        loadQuestions();
    }

    // Renders the game, including start box, end box, and the game itself
    void AbsurdQuestions::render() {
        ui_elements::InfoBox(
                _gameID,
                _showStartBox,
                "Startbox",
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this] {
                    start();
                }
        ).render();

        ui_elements::InfoBox(
                _gameID,
                _showEndBox,
                "Endbox",
                _endBoxTitle,
                _endBoxText,
                [this] {
                    reset();
                }
        ).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    // Renders the main game content
    void AbsurdQuestions::renderGame() {
        ui_elements::Window("Absurde Fragen").render([this]() {
            if (_questions.empty()) {
                std::cout << "No questions loaded." << std::endl;
                return;
            }

            if (_showCorrectMessage) {
                renderCorrectMessage();
            } else {
                renderQuestion();
            }
        });
    }

    // Renders the current question and answer options
    void AbsurdQuestions::renderQuestion() {

        float const buttonWidth {100.0f};
        float const buttonOffsetX {(ImGui::GetWindowWidth() - buttonWidth) / 2.0f};
        float const itemWidth {100.0f};
        float const itemOffsetX {(ImGui::GetWindowWidth() - itemWidth) / 2.0f};

        ImGui::PushFont(commons::Fonts::_header2);
        ui_elements::TextCentered(_currentQuestion.questionText.c_str());
        ImGui::PopFont();

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::SetCursorPosX(itemOffsetX);
        if (ImGui::RadioButton("Stimmt", _selectedOption)) {
            _selectedOption = true;
        }

        ImGui::SetCursorPosX(itemOffsetX);
        if (ImGui::RadioButton("Stimmt nicht", !_selectedOption)) {
            _selectedOption = false;
        }

        ImGui::Spacing();

        ImGui::SetCursorPosX(buttonOffsetX);

        if (ImGui::Button("Bestätigen")) {
            checkAnswer(_selectedOption);
        }
    }

    // Renders a message and current score when the correct answer is given
    void AbsurdQuestions::renderCorrectMessage(){
        auto now {std::chrono::steady_clock::now()};
        auto duration { std::chrono::duration_cast<std::chrono::seconds>(now - _correctMessageStartTime).count()};

        if (duration < 2) {
            ImGui::PushFont(commons::Fonts::_header2);
            ImGui::Spacing();
            ImGui::Spacing();
            ui_elements::TextCentered("Richtige Antwort!");
            ImGui::PopFont();
            _solvedText = "Du hast bisher " + std::to_string(_solved) + " Fragen richtig beantwortet";
            ui_elements::TextCentered(_solvedText.c_str());
            ImGui::Spacing();
            ui_elements::TextCentered(" Weiter so!");
        } else {
            _showCorrectMessage = false;
            generateRandomQuestion();
        }
    }

    // Renders the game over message in the endBox when an incorrect answer is given
    void AbsurdQuestions::renderGameOver() {
        stop();

        _endBoxTitle = "Das war leider nicht korrekt";
        _endBoxText = "Du hast diesmal " +
                      std::to_string(_solved) + " in Folge lösen können";
    }

    // Loads questions/answers from the questionnaire JSON file
    void AbsurdQuestions::loadQuestions() {
        logger::Logger& logger { logger::Logger::getInstance()};

        std::fstream file;
        try {
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            file.open("./config/games/absurd_questions.json");
            logger.log("Loading files for AbsurdQuestions-Game", QueueEntryType::INFORMATION);

            json data;
            file >> data;
            file.close();

            for (const auto &elem : data) {
                Question q;
                q.questionText = elem["frage"];
                q.isCorrectAnswer = elem["antwort"].get<int>() == 1; // Convert the answer to boolean
                _questions.emplace_back(q);
            }

            // Log the loaded questions
            for (const auto &q : _questions) {
                logger.log("Loaded question: " + q.questionText + " Answer: " + std::to_string(q.isCorrectAnswer), QueueEntryType::INFORMATION);
            }

        } catch (std::exception const &e) {
            std::stringstream error;
            error << "Error opening or reading the file absurd_questions.json: " << e.what();
            std::cerr << error.str() << std::endl;
            logger.log(error.str(), QueueEntryType::SEVERE);
        }
    }

    // Generates a random question from the loaded questions
    void AbsurdQuestions::generateRandomQuestion(){
        if (!_questions.empty()) {
            _currentQuestion = commons::RandomPicker::pickRandomElement(_questions);
        }
    }

    // Checks the selected answer and updates the game state
    void AbsurdQuestions::checkAnswer(bool selectedOption){
        if (selectedOption == _currentQuestion.isCorrectAnswer) {
            _solved++;
            _showCorrectMessage = true;
            _correctMessageStartTime = std::chrono::steady_clock::now();
            _selectedOption = false;
        } else {
            renderGameOver();
        }
    }

    // Starts the game by resetting counters and generating the first question
    void AbsurdQuestions::start() {
        _solved = 0;
        generateRandomQuestion();
        _isGameRunning = true;
        _showEndBox = false;
        _showStartBox = false;
        _selectedOption = false;
    }

    void AbsurdQuestions::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;
    }

    void AbsurdQuestions::reset() {
        start();
    }

    // Updates game statistics with the number of correct answers
    void AbsurdQuestions::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten", _solved);
    }

    std::string AbsurdQuestions::getName() const {
        return Game::getName();
    }
} // namespace game

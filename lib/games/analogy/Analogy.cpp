#include "Analogy.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

#include "Fonts.hpp"
#include "GameSessionManager.hpp"
#include "InfoBox.hpp"
#include "Logger.hpp"
#include "TextCentered.hpp"
#include "Window.hpp"

using json = nlohmann::json;

namespace games {
    // Constructor: Initializes the game with name, description, rules, controls, and loads questions
    Analogy::Analogy() : Game(abstract_game::GameID::ANALOGY), _selectedOption{'\0'} {
        _gameName = "Analogien";
        _gameDescription = "Finde das passende Wort.";
        _gameRules = "1. Analysiere die angezeigte Wortverbindung.\n2. Finde das dazu passende Wort.\n"
                "3. Bestätige deine Auswahl mit dem Button.\n";
        _gameControls = "Linke Maustaste zur Auswahl der Antwort und ebenfalls zum Bestätigen des Buttons";

        loadQuestions();
    }

    // Renders the game, including start box, end box, and the game itself
    void Analogy::render() {
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
    void Analogy::renderGame() {
        ui_elements::Window("Analogien").render([this] {
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
    void Analogy::renderQuestion() {
        static constexpr float BUTTON_WIDTH{100.0f};
        float const buttonOffsetX{(ImGui::GetWindowWidth() - BUTTON_WIDTH) / 2.0f};
        static constexpr float ITEM_WIDTH{100.0f};
        float const itemOffsetX{(ImGui::GetWindowWidth() - ITEM_WIDTH) / 2.0f};

        ImGui::PushFont(commons::Fonts::_header2);
        ui_elements::TextCentered(_currentQuestion.questionText.c_str());
        ImGui::PopFont();

        ImGui::Spacing();
        ImGui::Spacing();

        for (const auto &[fst, snd]: _currentQuestion.options) {
            ImGui::SetCursorPosX(itemOffsetX);
            std::string const label{"  " + snd};
            if (ImGui::RadioButton(label.c_str(), _selectedOption == fst)) {
                _selectedOption = fst;
            }
        }

        ImGui::Spacing();

        ImGui::SetCursorPosX(buttonOffsetX);

        if (ImGui::Button("Bestätigen")) {
            checkAnswer(_selectedOption);
        }
    }

    // Renders a message and current score when the correct answer is given
    void Analogy::renderCorrectMessage() {
        auto const now{std::chrono::steady_clock::now()};

        if (auto const duration{std::chrono::duration_cast<std::chrono::seconds>(now - _correctMessageStartTime).count()}; duration < 2) {
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
    void Analogy::renderGameOver() {
        stop();

        _endBoxTitle = "Das war leider nicht korrekt";
        _endBoxText = "Du hast diesmal " +
                      std::to_string(_solved) + " in Folge lösen können\n\n"
                      + "Die Lösung der letzten Aufgabe lautet:\n\n" + _currentQuestion.explanation;
    }

    // Loads questions/answers from the questionnaire JSON file
    void Analogy::loadQuestions() {
        logger::Logger &logger{logger::Logger::getInstance()};

        try {
            std::fstream file;
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            file.open("assets/games/analogy/questionnaire.json");
            logger.log("Loading files for Analogy-Game", logger::LogType::INFORMATION);

            json data;
            file >> data;
            file.close();

            for (auto const &elem: data["questionnaire"]) {
                Question q;
                q.questionText = elem["question"];
                q.options['a'] = elem["options"]["a"];
                q.options['b'] = elem["options"]["b"];
                q.options['c'] = elem["options"]["c"];
                q.options['d'] = elem["options"]["d"];
                q.correctAnswer = elem["correct_answer"].get<std::string>()[0];
                q.explanation = elem["explanation"];
                _questions.emplace_back(q);
            }
        } catch (std::exception const &e) {
            std::stringstream error;
            error << "Error opening or reading the file questionnaire.json: " << e.what();
            std::cerr << error.str() << std::endl;
            logger.log(error.str(), logger::LogType::SEVERE);
        }
    }

    // Generates a random question from the loaded questions
    void Analogy::generateRandomQuestion() {
        if (!_questions.empty()) {
            _currentQuestion = commons::RandomPicker::pickRandomElement(_questions);
        }
    }

    // Checks the selected answer and updates the game state
    void Analogy::checkAnswer(char const &selectedOption) {
        if (selectedOption == _currentQuestion.correctAnswer) {
            _solved++;
            _showCorrectMessage = true;
            _correctMessageStartTime = std::chrono::steady_clock::now();
            _selectedOption = '\0';
        } else {
            renderGameOver();
        }
    }

    // Starts the game by resetting counters and generating the first question
    void Analogy::start() {
        _solved = 0;
        generateRandomQuestion();
        _isGameRunning = true;
        _showEndBox = false;
        _showStartBox = false;
        _selectedOption = '\0';
    }

    void Analogy::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;
    }

    void Analogy::reset() {
        start();
    }

    // Updates game statistics with the number of correct answers
    void Analogy::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten", _solved);
    }
} // games

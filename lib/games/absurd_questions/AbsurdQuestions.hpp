#ifndef ATHENA_ABSURD_QUESTIONS_HPP
#define ATHENA_ABSURD_QUESTIONS_HPP

#include "Logger.hpp"
#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>
#include "UiElement.hpp"
#include "InfoBox.hpp"
#include "Window.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "Centered.hpp"
#include "RandomPicker.hpp"
#include <chrono>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include "GameIDs.hpp"

namespace game {

    /**
     * @brief The AbsurdQuestions game class, which represents the logic and rendering of the game.
     */
    class AbsurdQuestions : public abstract_game::Game {

        /**
         * @brief A structure representing a question in the absurd questions game.
         */
        struct Question {
            std::string questionText;
            bool isCorrectAnswer;
        };

        sf::Clock _colorClock;
        std::vector<Question> _questions;
        bool _isAnswerCorrect{false};
        bool _showCorrectMessage{false};
        std::chrono::steady_clock::time_point _correctMessageStartTime;
        int _solved{0};
        std::string _solvedText;
        Question _currentQuestion;
        bool _selectedOption;

        /**
         * @brief Loads the list of questions.
         */
        void loadQuestions();

        /**
         * @brief Generates a random question from the loaded list.
         */
        void generateRandomQuestion();

        /**
         * @brief Checks if the selected answer is correct.
         * @param selectedOption The selected answer option.
         */
        void checkAnswer(bool selectedOption);

        /**
         * @brief Renders the current question and answer options.
         */
        void renderQuestion();

        /**
         * @brief Renders the message for a correct answer.
         */
        void renderCorrectMessage();

        /**
         * @brief Renders the endbox texts.
         */
        void renderGameOver();

    public:

        AbsurdQuestions();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;
    };
}

#endif // ATHENA_ABSURD_QUESTIONS_HPP

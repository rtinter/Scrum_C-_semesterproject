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
#include <nlohmann/json.hpp>
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
        /**
         * @brief Constructor for the AbsurdQuestions game.
         */
        AbsurdQuestions();

        /**
         * @brief Renders the game.
         */
        void render() override;

        /**
         * @brief Renders the game logic.
         */
        void renderGame() override;

        /**
         * @brief Starts the game.
         */
        void start() override;

        /**
         * @brief Stops the game.
         */
        void stop() override;

        /**
         * @brief Resets the game state.
         */
        void reset() override;

        /**
         * @brief Updates the game statistics.
         */
        void updateStatistics() override;

        /**
         * @brief Returns the name of the game.
         * @return The name of the game.
         */
        std::string getName() const override;
    };

} // namespace game

#endif // ATHENA_ABSURD_QUESTIONS_HPP

#pragma once

#include <chrono>
#include <map>
#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "Logger.hpp"
#include "RandomPicker.hpp"

namespace games {
    /**
     * @brief The Analogy game class, which represents the logic and rendering of the game.
     */
    class Analogy final : public abstract_game::Game {
        /**
          * @brief A structure representing a question in the analogy game.
          */
        struct Question {
            std::string questionText;
            std::map<char, std::string> options;
            char correctAnswer;
            std::string explanation;
        };

        sf::Clock _colorClock;
        std::vector<Question> _questions;
        bool _showCorrectMessage{false};
        std::chrono::steady_clock::time_point _correctMessageStartTime;
        int _solved{0};
        std::string _solvedText;
        Question _currentQuestion;
        char _selectedOption;

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
        void checkAnswer(char const &selectedOption);

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
         * @brief Constructor for the Analogy game.
         */
        explicit Analogy();

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
    };
} // games

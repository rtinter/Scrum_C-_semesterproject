#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/System/Clock.hpp>

#include "Game.hpp"
#include "InfoBox.hpp"
#include "Logger.hpp"

namespace games {
    /**
     * @brief The Conclusions game class, which represents the logic and rendering of the game.
     */
    class Conclusions final : public abstract_game::Game {
        /**
         * @brief A structure representing a question in the absurd questions game.
         */
        struct Question {
            std::string questionText;
            bool isCorrectAnswer;
        };

        sf::Clock _colorClock;
        std::vector<Question> _questions;
        bool _showCorrectMessage;
        std::chrono::steady_clock::time_point _correctMessageStartTime;
        int _solved;
        std::string _solvedText;
        Question _currentQuestion;
        std::optional<bool> _selectedOption;
        std::optional<Question> _lastQuestion;

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
        void checkAnswer(std::optional<bool> const &selectedOption);

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
        Conclusions();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;
    };
} // game

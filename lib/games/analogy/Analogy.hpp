#pragma once

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
#include "chrono"
#include "SFML/System/Clock.hpp"

namespace game {

    class Analogy : public abstract_game::Game {

        struct Question {
            std::string questionText;
            std::map<char, std::string> options;
            char correctAnswer;
            std::string explanation;
        };

        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        sf::Clock _colorClock;

        std::vector<Question> _questions;
        bool _showCorrectMessage;
        std::chrono::steady_clock::time_point _correctMessageStartTime;
        int _solved {0};
        std::string _solvedText;
        Question _currentQuestion;

    public:

        explicit Analogy();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        virtual std::string getName() const override;

    private:
        void loadQuestions();

        void generateRandomQuestion();

        void checkAnswer(char selectedOption);

        void renderQuestion();

        void renderCorrectMessage();

        void renderGameOver();
    };
}
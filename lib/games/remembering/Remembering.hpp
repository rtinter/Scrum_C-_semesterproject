#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Game.hpp"
#include "QuestionBank.hpp"
#include "Timer.hpp"
#include "Window.hpp"
#include "UiElement.hpp"
#include "Scene.hpp"
#include "Remembering.hpp"
#include <Centered.hpp>
#include <DashboardScene.hpp>
#include <Fonts.hpp>
#include <InfoBox.hpp>
#include <Overlay.hpp>
#include <SceneManager.hpp>
#include <TextCentered.hpp>
#include <Window.hpp>
#include <sstream>
#include <algorithm>

namespace games {

    class Remembering : public abstract_game::Game {
    public:
        explicit Remembering();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

    private:
        std::string _userTextBuffer;
        bool _showText{true};
        bool _showContinueButton{false};
        bool _submitted{false};
        int _score{0};
        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;
        ui_elements::Timer _timer{"Remembering Game", 30};
        static std::vector<int> _selectedAnswers;

        std::unique_ptr<QuestionBank> _questionBank;
        QuestionBank::QuestionSet _currentQuestionSet;

        void displayCenteredText(const std::string &text) const;

        void selectRandomQuestionSet();

        std::string displayEvaluation(int const &score, int const &size) const;

        void renderQuestion(int index, const QuestionBank::Question &q, int &selectedAnswer) const;

        void setStyles();

        void renderSubmitButtons();
    };

}

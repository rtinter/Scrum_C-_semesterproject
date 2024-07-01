#pragma once

#include "Game.hpp"
#include "GameIDs.hpp"
#include "DiagramQuestion.hpp"
#include "imgui-SFML.h"
#include <map>

namespace games {
    class DiagramAnalysis : public abstract_game::Game {
    private:
        std::vector<DiagramQuestion> _questions;
        std::map<std::string, sf::Texture> _textures;
        std::map<std::string, bool> _answers;

        DiagramQuestion _currentQuestion;
        int _currentQuestionIndex{0};
        int _score{0};
        void checkAnswers();

    public:
        DiagramAnalysis();
        std::string getName() const override;
        void renderGame() override;
        void stop() override;
        void updateStatistics() override;
        void start() override;
        void reset() override;
        void render() override;
    };
}

#pragma once

#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>
#include "UiElement.hpp"
#include "InfoBox.hpp"
#include "Window.hpp"
#include "Fonts.hpp"

#include "SFML/System/Clock.hpp"

namespace game {
    /******************************************************
    KOMMENTAR
    **************************************************+***/

    class Analogy : public abstract_game::Game {

        struct Question {
            std::string questionText;
            std::unordered_map<char, std::string> options;
            char correctAnswer;
            std::string explanation;
        };

        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        sf::Clock _colorClock;

        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;

        std::vector<Question> questions;

    public:

        explicit Analogy();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        virtual std::string getName() const override;

        void loadQuestions();

    };
}

#pragma once

#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>

#include "SFML/System/Clock.hpp"

namespace games {
    /******************************************************
    KOMMENTAR FÜR DAS SPIEL
    **************************************************+***/

    class Remembering : public Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};

        //float _redDuration{0};
        std::string _userTextBuffer;
        sf::Clock _colorClock;
        //std::chrono::steady_clock::time_point _startPoint, _finishPoint;

        // static std::string getDurationRating(int duration);


        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;


    public:
        explicit Remembering();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;
    };
}

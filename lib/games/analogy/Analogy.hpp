#pragma once

#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>

#include "SFML/System/Clock.hpp"

namespace games {
    /******************************************************
    KOMMENTAR
    **************************************************+***/

    class Analogy : public abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        sf::Clock _colorClock;

    public:
        explicit Analogy();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;
    };
}

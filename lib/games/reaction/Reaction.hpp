#pragma once

#include <chrono>
#include <Game.hpp>
#include <imgui.h>

#include "SFML/System/Clock.hpp"
#include "Colors.hpp"

namespace games {
    /******************************************************
     *<b>Reaction Test Game</b><br>
     *
     *Reaction ist ein einfaches, aber spannendes Spiel, das deine Reflexe auf die Probe stellt.<br>
     * Warte, bis der Bildschirm von Rot zu Grün wechselt, und klicke so schnell wie möglich die linke Maustaste,
     * um deine Reaktionszeit in Millisekunden zu messen.
    **************************************************+***/

    class Reaction : public abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::RED};
        float _redDuration{0};

        sf::Clock _colorClock;
        std::chrono::steady_clock::time_point _startPoint, _finishPoint;

        /**
         * @brief This method returns a rating based on the duration.
         *
         * @param duration The duration.
         * @return The rating.
         */
        static std::string getDurationRating(int duration);

        /**
         * @brief This method checks if the window color is green.
         *
         * @return True if the window color is green, false otherwise.
         */
        bool isGreen() const;

    public:
        explicit Reaction();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override ;
    };

} // reaction

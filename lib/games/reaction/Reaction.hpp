#pragma once

#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>

#include "SFML/System/Clock.hpp"

namespace reaction {
    /******************************************************
     *<b>Reaction Test Game</b><br>
     *
     *Reaction ist ein einfaches, aber spannendes Spiel, das deine Reflexe auf die Probe stellt.<br>
     * Warte, bis der Bildschirm von Rot zu Grün wechselt, und klicke so schnell wie möglich die linke Maustaste,
     * um deine Reaktionszeit in Millisekunden zu messen.
    **************************************************+***/

    class Reaction : public Game {
        ImVec4 _windowColor{commons::Colors::RED};
        float _redDuration{0};

        sf::Clock _colorClock;
        std::chrono::steady_clock::time_point _startPoint, _finishPoint;

        static std::string getDurationRating(int duration);

        bool isGreen() const;

        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;

    public:
        explicit Reaction();

        void render() override;

        void renderGame() override;

        void start() override;


        void stop() override;

        void reset() override;

        void updateStatistics() override;
    };
} // reaction

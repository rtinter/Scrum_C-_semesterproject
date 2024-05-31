#ifndef ATHENA_REACTION_H
#define ATHENA_REACTION_H


#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <random>
#include <ctime>   // For std::time
#include <chrono>  // For std::chrono
#include <iostream>
#include "../../lib/abstract_game/Game.hpp"
#include "../../lib/commons/Fonts.hpp"
#include "../../lib/commons/Colors.hpp"
#include "../../lib/commons/ColorTheme.hpp"
#include "../../lib/commons/StyleManager.hpp"


namespace reaction {
    /******************************************************
     *<b>Reaction Test Game</b><br>
     *
     *Reaction ist ein einfaches, aber spannendes Spiel, das deine Reflexe auf die Probe stellt.<br>
     * Warte, bis der Bildschirm von Rot zu Grün wechselt, und klicke so schnell wie möglich die linke Maustaste,
     * um deine Reaktionszeit in Millisekunden zu messen.
     **************************************************+***/

    class Reaction : public Game {

        std::string const _kNAME{"Reaction"};
        ImVec2 _size;
        bool _isOpen;

        ImVec4 _windowColor;
        sf::Clock _deltaClock;

        sf::Clock _colorClock; // Clock to track the duration of the color change
        bool _isRed, _isRunning;
        float _redDuration;
        std::chrono::steady_clock::time_point _startPoint, _finishPoint;

        static std::string getDurationRating(int duration);

    public:
        explicit Reaction();

        void start() override;

        void reset() override;

        void updateStatistics() override;

        void render();


        void turnGreen();

    };

} // reaction

#endif //ATHENA_REACTION_H

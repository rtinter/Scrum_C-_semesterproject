//
// Created by zepi on 16.05.24.
//

#ifndef ATHENA_REACTION_H
#define ATHENA_REACTION_H


#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <cstdlib> // For std::rand and std::srand
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
     * Reaction Test Game
     *
     **************************************************+***/

    class Reaction : public Game{

        std::string const _kNAME {"Reaction"};
        ImVec2 _size;
        bool _isOpen;
        bool _isClicked;
        bool _wasReset;

        ImVec4 _windowColor;
        sf::Clock _deltaClock;

        sf::Clock _colorClock; // Clock to track the duration of the color change
        bool _isRed, _isRunning;
        float _redDuration;
        std::chrono::time_point<std::chrono::system_clock> _startPoint, _finishPoint;


        static std::string getDurationRating(int duration);

    public:
        Reaction();

        //explicit Reaction(ImVec2 const &size);

        void start() override;

        void reset() override;
        void render();
        void setup();
        void updateStatistics() override;

        void updateColor();

    };

} // reaction

#endif //ATHENA_REACTION_H

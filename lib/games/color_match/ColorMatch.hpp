#ifndef ATHENA_COLORMATCH_H
#define ATHENA_COLORMATCH_H

#include <string>
#include <random>
#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"

namespace games {

    class ColorMatch : public Game {
        int _numberOfRandomColors{3};
        bool _isTimeForNewRandomColors;
        int _indexOfCurrentColor;
        int _numberOfCorrectClicksInTotal;
        int _numberOfCorrectClicksSinceLastError;
        int _longestStreak;
        std::string _endboxString;
        enum GameMode {
            MATCH_IMVEC4, // click text button according to font color
            MATCH_STRING  // click color button according to word
        };
        GameMode _currentGameMode;
        ui_elements::Timer _timer{"Color Match Game", 60};

        std::vector<std::string> const _AVAILABLE_COLORS_STRING{"rot", "blau", "gelb", "lila", "grün"};
        std::vector<ImVec4> const _AVAILABLE_COLORS_IMVEC4{commons::Colors::RED, commons::Colors::BLUE,
                                                           commons::Colors::YELLOW, commons::Colors::PURPLE,
                                                           commons::Colors::GREEN};
        std::vector<std::string> _randomColorsString;
        std::vector<ImVec4> _randomColorsImVec4;
        std::array<std::string, 3> const _clickedColors;

        void displayRandomColors();

        void pickRandomColorsText();

        void pickRandomColorsImVec4();

    public:
        ColorMatch();

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void updateStatistics() override;

        void displayColorButtons();

        void stop();

        void onClick(bool isCurrentColor);
    };

}

#endif //ATHENA_COLORMATCH_H

#ifndef ATHENA_SEQUENCE_H
#define ATHENA_SEQUENCE_H

#include <array>
#include "Game.hpp"

namespace sequence {

    class Sequence : public abstract_game::Game {

        enum GameMode {
            WATCH,  //watch the sequence and try to remember it
            REPEAT  //repeat the sequence you just saw
        };
        GameMode _currentGameMode;

        int _levelCounter;
        std::string _endBoxString;
        int _longestReproducedSequence{0};

        static int constexpr _NUMBER_OF_BUTTONS{9};
        std::chrono::steady_clock::time_point _startHighlightingHere;
        std::chrono::steady_clock::time_point _stopHighlightingHere;
        int _lightUpDurationInSeconds{1};
        int _sequenceButtonIterator;        //to be used in both gamemodes -> for iterating through sequence during show and repeat
        int _correctClicksOfCurrentSequence;
        bool _wasLastButtonOfSequence{false};
        bool _canShowNextButtonInSequence{true};    //in the beginning, no button is lit up

        std::vector<int> _buttonsClickedSequence;
        //true -> Button lights up
        std::array<int, _NUMBER_OF_BUTTONS> _buttonStatess;


        //TODO kurze Wartezeit zwischen light up buttons, falls Buttons zweimal hintereinander aufleuchten

        void displayButtons();

        void isClickedInCorrectOrder(int const &buttonID);

        void chooseNextRandomButton();

        void showSequence();

        void lightUp(int &buttonState);

        void checkLitUpExpired(int &buttonState);

        void nextLevel();

        void switchGameMode();

        void moveOnToNextButton();

    public:
        Sequence();

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void stop() override;

        void updateStatistics() override;

    };

} // sequence

#endif //ATHENA_SEQUENCE_H

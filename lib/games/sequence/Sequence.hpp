#ifndef ATHENA_SEQUENCE_H
#define ATHENA_SEQUENCE_H

#include "Game.hpp"

namespace sequence {

    class Sequence : public abstract_game::Game {

        std::string _endBoxString;
        int _longestReproducedSequence;

        static int constexpr _NUMBER_OF_BUTTONS {9};

        int _levelCounter;

        std::vector<int> _buttonsClickedSequence;
        //true -> Button lights up
        std::vector<bool> _buttonStates;



        void displayButtons();

        void isClickedInCorrectOrder();

        void chooseNextRandomButton();

        void showSequence();

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

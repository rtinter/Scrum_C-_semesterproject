#ifndef ATHENA_SEQUENCE_H
#define ATHENA_SEQUENCE_H

#include <array>
#include "Game.hpp"

namespace sequence {

    /**
     * Sequence is a game meant to test the user's ability to memorize an ever growing sequence of buttons they need to press
     * in the right order. Each button also plays a sound in different pitches to further support the user's memory.
     */
    class Sequence : public abstract_game::Game {

        /**
         * Enums to switch between two different modes in the game. WATCH for letting the computer play the sequence and
         * then REPEAT so the user can take over again and repeat the sequence they just saw.
         */
        enum GameMode {
            WATCH,  // watch the sequence and try to remember it
            REPEAT  // repeat the sequence you just saw
        };
        GameMode _currentGameMode;

        int _levelCounter;  // keeps track of the user's level, aka the length of the current sequence as it gets longer with each round
        int _longestReproducedSequence{0};
        std::string _endBoxString;


        static int constexpr _NUMBER_OF_BUTTONS{9};

        // chrono timepoints to program the lighting up of the different buttons with appropriate wait times without having to use threads
        // that would stop the entire gameloop
        std::chrono::steady_clock::time_point _stopHighlightingHere;
        std::chrono::steady_clock::time_point _stopWaitingHere;

        int _waitDurationInMilliseconds{300};
        int _lightUpDurationInMilliseconds{800};

        /**
         * Iterator used in both gamemodes -> for iterating through the sequence during show and repeat
         */
        int _sequenceButtonIterator;

        /**
         * keeps track of the correct clicks a user has made, to switch back to the WATCH game mode if the user
         * correctly repeated the entire sequence
         */
        int _correctClicksOfCurrentSequence;
        bool _wasLastButtonOfSequence{false};

        /**
         * boolean to ensure only one button is lit up at once,
         * initialized as true because in the beginning, no button is lit up
         */
        bool _canShowNextButtonInSequence{true};
        bool _mustWait{false};

        std::vector<int> _buttonsClickedSequence;
        /**
         * Array keeping track of the states (lit or not lit up) of all nine buttons
         */
        std::array<int, _NUMBER_OF_BUTTONS> _buttonStates;


        /**
         * Called in renderGame()<br>
         * Displays the buttons according to the Gamemode (clickable for REPEAT, non-clickable for WATCH) and also
         * handles all the logic that takes care of displaying the current sequence in WATCH Gamemode with our non-thread
         * implementation.
         */
        void displayButtons();

        /**
         * Called each time the user presses a button in REPEAT mode.<br>
         * Checks, if each button clicked by the player is the current correct one. If it is, the
         * game continues and the player has to click the next right button or, if he correctly repeated the entire sequence,
         * the Gamemode switches to WATCH (next level) and the Computer elongates the sequence.<br>
         * If the clicked button is false, the player gets a Game Over.
         * @param buttonID ID of the clicked button
         */
        void isClickedInCorrectOrder(int const &buttonID);

        /**
         * Called in the very beginning and each time the GameMode is switched from REPEAT to WATCH (indicating the
         * start of a new level).<br>
         * It generates a random number in the range of 1 to 9 to choose the next button to light up to elongate the
         * random sequence for each new level.
         */
        void chooseNextRandomButton();

        /**
         * Called each time WATCH Gamemode is started so the new sequence is displayed by the computer for the user to
         * memorize. Is called again, after the wait time between >=2 buttons in sequence in checkWaitTimeExpired() so
         * that all buttons in sequence are shown and not just one. <br>
         * The method ensures, that only one button at once and only the correct button in sequence lights up for a
         * certain amount of time and also ensures that no button lights up during the short wait time between button
         * light ups.
         */
        void showSequence();

        /**
         * Called in showSequence() to light up buttons of sequence and play sound.
         * Sets a chrono timepoint 800ms in future to stop lighting the button (non-thread implementation).
         * @param buttonState reference to buttonState of certain button from the array that handles all button states,
         * to switch it to 1 (lit up)
         * @param buttonID button ID of the button that is supposed to light up
         */
        void lightUp(int &buttonState, int const &buttonID);

        /**
         * Called in displayButtons() to constantly check during the gameloop, if the chrono timepoint of a lit up button
         * has been reached, indicating that the button has to be switched off.
         * @param buttonState reference to buttonState of certain button from the array that handles all button states,
         * to check if its state is 1 (lit up)
         */
        void checkLitUpExpired(int &buttonState);

        /**
         * Called each time a user correctly repeats an entire sequence and increases the level counter by +1 so the
         * next sequence will be one button longer.
         */
        void nextLevel();

        /**
         * Switches the current GameMode to the other GameMode so the user can repeat the sequence or so the game can
         * get to the next level and show the new sequence to the user again.
         */
        void switchGameMode();

        /**
         * Increase iterator that runs through button sequence to check/light up the next button.
         */
        void moveOnToNextButton();

        /**
         * Called whenever a button that has been lit up is switched off.<br>
         * It ensures that there is a short wait time in between all buttons during the WATCH Gamemode so that it's
         * easier for the user to follow and memorize the shown sequence.
         */
        void waitInBetweenButtons();

        /**
         * Called in displayButtons() to constantly check during the gameloop, if the chrono timepoint of a wait time
         * in between buttons while the sequence is shown has been reached, indicating that the next button would be
         * allowed to light up now OR, if the end of the sequence has been reached, that the GameMode can switch to REPEAT.
         */
        void checkWaitTimeExpired();

        /**
         * Plays the correct sound for each of the nine buttons either during WATCH mode or when the user clicks the button
         * themselves in REPEAT mode.
         * @param buttonID ID of the clicked/activated button
         */
        static void playButtonSound(int const &buttonID);

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

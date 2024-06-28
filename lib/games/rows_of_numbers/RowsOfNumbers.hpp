#ifndef ATHENA_ROWSOFNUMBERS_HPP
#define ATHENA_ROWSOFNUMBERS_HPP

#include <Game.hpp>
#include <imgui.h>
#include <Colors.hpp>
#include <WordTarget.hpp>
#include "Sequence.hpp"

namespace game {

    class RowsOfNumbers : abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        int _input{0};
        int _solvedCounter{0};
        int _randomSequence;
        std::string _currentSequence;
        int _currentSolution;
        std::string _currentExplanation;
        std::chrono::steady_clock::time_point _correctAnswerTime;
        bool _waitingForNextNumber{false};
        bool _inputChanged{false};
        static std::vector<game::Sequence> _sequences;

        static void loadWordsFromFile();

    public:
        RowsOfNumbers();

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void updateStatistics() override;

        void stop() override;

        std::string getName() const override;

        int randomIndexGenerator(int size) const;

        ~RowsOfNumbers() override;
    };

} // game

#endif //ATHENA_ROWSOFNUMBERS_HPP

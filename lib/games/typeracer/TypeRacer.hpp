#ifndef ATHENA_TYPERACER_H
#define ATHENA_TYPERACER_H

#include "Game.hpp"
#include "imgui.h"
#include <Colors.hpp>
#include <set>

namespace typeracer {

    /******************************************************
     *<b>Type Racer Game</b><br>
     *
     * Type Racer ist gibt dem User zwei Sätze und misst die Geschwindigkeit der Tastenanschläge, sowie zeigt richtige
     * und falsche Buchstaben.
    **************************************************+***/

    class TypeRacer : public abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        float _windowWidth;
        float _textWidth;
        std::string _sentence;
        std::set<int> _mistypedIndices;
        std::chrono::steady_clock::time_point _startPoint;
        bool _runTimer{false};
        float _wpm{0.0f};
        char _input[256];
        int _randomIndex{0};

    public:
        explicit TypeRacer();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;

        ~TypeRacer() override;
    };

} // typeracer

#endif //ATHENA_TYPERACER_H

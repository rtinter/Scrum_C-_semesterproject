#ifndef ATHENA_TYPERACER_H
#define ATHENA_TYPERACER_H

#include "Game.hpp"
#include "imgui.h"
#include <Colors.hpp>

namespace typeracer {

    /******************************************************
     *<b>Type Racer Game</b><br>
     *
     * Type Racer ist gibt dem User zwei Sätze und misst die Geschwindigkeit der Tastenanschläge, sowie zeigt richtige
     * und falsche Buchstaben.
    **************************************************+***/

    class TypeRacer : public Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
        int _mistakes {0};
        std::chrono::steady_clock::time_point _startPoint;
        bool _run_timer {false};
        float _wpm {0.0f};
        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;

    public:
        explicit TypeRacer();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;
    };

} // typeracer

#endif //ATHENA_TYPERACER_H

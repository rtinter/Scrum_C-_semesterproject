#ifndef ATHENA_ROWSOFNUMBERS_HPP
#define ATHENA_ROWSOFNUMBERS_HPP

#include <Game.hpp>
#include <imgui.h>
#include <Colors.hpp>

namespace game {

    class RowsOfNumbers : abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::LIGHT_GRAY};
    public:
        RowsOfNumbers();
        void render() override;
        void renderGame() override;
        void start() override;
        void reset() override;
        void updateStatistics() override;
        void stop() override;
        std::string getName() const override;
        ~RowsOfNumbers() override;
    };

} // game

#endif //ATHENA_ROWSOFNUMBERS_HPP

//
// Created by Admin on 15.06.2024.
//

#ifndef ATHENA_MEMORY_HPP
#define ATHENA_MEMORY_HPP

#include "Game.hpp"
#include <imgui.h>

namespace memory {

    class Memory : public abstract_game::Game {
        // Add private members here


    public:
        explicit Memory();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;

    };

} // memory

#endif //ATHENA_MEMORY_HPP

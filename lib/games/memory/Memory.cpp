//
// Created by Admin on 15.06.2024.
//

#include "Memory.hpp"
#include "GameSessionManager.hpp"

namespace memory{

    Memory::Memory() : abstract_game::Game(abstract_game::GameID::MEMORY){

    }

    void Memory::render() {

    }

    void Memory::renderGame() {

    }

    void Memory::start() {

    }

    void Memory::stop() {
        Game::stop();
    }

    void Memory::reset() {

    }

    void Memory::updateStatistics() {

    }

    std::string Memory::getName() const {
        return Game::getName();
    }


}
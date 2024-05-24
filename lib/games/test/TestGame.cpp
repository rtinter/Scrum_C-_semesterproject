//
// Created by jo on 5/23/24.
//

#include "TestGame.hpp"
#include <iostream>

#include <SFML/Graphics.hpp>

void TestGame::start() {
    std::cout << "Starting game" << std::endl;
}

void TestGame::stop() {
    std::cout << "stopping game" << std::endl;
}

void TestGame::update() {
    std::cout << "updating window" << std::endl;
}

void TestGame::render() {
    std::cout << "render" << std::endl;
}

void TestGame::handleEvents(sf::Event evt) {
    std::cout << "Handling Events" << std::endl;
}

std::string TestGame::getGameInfo() {
    return "Test Game";
}

void TestGame::updateStatistics() {}
void TestGame::reset() {}

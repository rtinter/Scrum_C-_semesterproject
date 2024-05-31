#include "App.hpp"
#include "../lib/abstract_game/GameSession.hpp"
#include <iostream>
#include <thread>

int main() {
    GameSession session1(1, 1001);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    session1.end();

    std::cout << "Session 1 ended" << std::endl;
    std::cout << "Game ID: " << session1.getGameID() << std::endl;
    std::cout << "User ID: " << session1.getUserID() << std::endl;
    std::cout << "Game Session UID: " << session1.getGameSessionUID() << std::endl;
    std::cout << "Duration: " << session1.getDurationInSeconds() << " seconds" << std::endl;

    GameSession session2(2, 1002);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    session2.end();

    std::cout << "Session 2 ended" << std::endl;
    std::cout << "Game ID: " << session2.getGameID() << std::endl;
    std::cout << "User ID: " << session2.getUserID() << std::endl;
    std::cout << "Game Session UID: " << session2.getGameSessionUID() << std::endl;
    std::cout << "Duration: " << session2.getDurationInSeconds() << " seconds" << std::endl;

    std::cout << "Check the game_session.csv file for the session data." << std::endl;
    App::start();
    return 0;
}

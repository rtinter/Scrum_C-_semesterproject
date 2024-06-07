#include "App.hpp"
#include <iostream>
#include "GameSession.hpp"

int main() {
    // Create a game session
    abstract_game::GameSession session(1, 1001);

    // Add some game run-throughs
    session.addNewGameRunThrough("seconds", 150);
    session.addNewGameRunThrough("seconds", 200);
    session.addNewGameRunThrough("points", 300);

    // End the session
    session.end();

    // Write the run-throughs to a CSV file
    session.writeRunThroughsToCsv("game_runthroughs.csv");

    std::cout << "Game run-throughs written to CSV." << std::endl;
    App::start();
    return 0;
}

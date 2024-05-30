#include <sstream>
#include "GameSession.hpp"

GameSession::GameSession(int gameID, int userID) : gameID {gameID}, userID {userID}, gameSessionUID {calcGameSessionUID()}, startPoint {std::chrono::steady_clock::now()}, ended {false} { }

size_t GameSession::calcGameSessionUID() {

    // get current timeString as string
    std::string timeString = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

    // get random value as string
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    std::srand(nanos);
    std::string randomString = std::to_string(std::rand() % 1000 + 1);

    // concatenate timeString and random value for hash input
    std::stringstream ss;
    ss << timeString << randomString;
    std::string hashInput {ss.str()};

    // create hash from input
    size_t hash {std::hash<std::string>{}(hashInput)};

    return hash;
}

void GameSession::end() {
    ended = true;

    // save the current time as the end time of the game session
    endPoint = std::chrono::steady_clock::now();
}
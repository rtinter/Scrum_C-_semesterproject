#include <sstream>
#include "GameSession.hpp"

GameSession::GameSession(int gameID, int userID) : _gameID {gameID}, _userID {userID}, _gameSessionUID {calcGameSessionUID()}, _startPoint {std::chrono::steady_clock::now()}, _ended {false} { }

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
    _ended = true;

    // save the current time as the end time of the game session
    _endPoint = std::chrono::steady_clock::now();
}

unsigned long long GameSession::getDurationInSeconds() const {
    if(!_ended) {
        // game session is still running
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _startPoint).count();
    }
    else{
        // game session has ended
        return std::chrono::duration_cast<std::chrono::seconds>(_endPoint - _startPoint).count();
    }
}

void GameSession::addNewGameRunThrough(size_t const &gameSessionUID, std::string const &resultUnit, long const &result) {

    increaseRunThroughCount();
    _gameRunThroughs.emplace_back(gameSessionUID, _runThroughCount, resultUnit, result);
}

void GameSession::increaseRunThroughCount() {
    _runThroughCount++;
    //TODO bool Wert zur Absicherung hinzufügen, damit Funktion weniger unnötig ist??
}
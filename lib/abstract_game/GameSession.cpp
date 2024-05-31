#include <sstream>
#include <fstream>
#include <iostream>
#include "GameSession.hpp"
#include "DataManagerFactory.hpp"

GameSession::GameSession(int gameID, int userID) : _gameID {gameID}, _userID {userID},
    _gameSessionUID {calcGameSessionUID()}, _startPoint {std::chrono::steady_clock::now()}, _ended {false},
    _dataManager {DataManagerFactory::Create("CsvManager")}
    { }

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
    writeToDataManager();
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

int GameSession::getGameID() const {
    return _gameID;
}

int GameSession::getUserID() const {
    return _userID;
}

size_t GameSession::getGameSessionUID() const {
    return _gameSessionUID;
}

std::chrono::steady_clock::time_point GameSession::getStartPoint() const {
    return _startPoint;
}

std::chrono::steady_clock::time_point GameSession::getEndPoint() const {
    return _endPoint;
}

bool GameSession::isEnded() const {
    return _ended;
}

void GameSession::writeToDataManager() const {
    long long startTime = std::chrono::duration_cast<std::chrono::seconds>(_startPoint.time_since_epoch()).count();
    long long endTime = _ended ? std::chrono::duration_cast<std::chrono::seconds>(_endPoint.time_since_epoch()).count() : 0;
    unsigned long long duration = getDurationInSeconds();
    _dataManager->saveGameSession(_gameSessionUID, _userID, _gameID, startTime, endTime, duration, _ended);
}

void GameSession::writeToCsv(const std::string& filename) const {
    std::ofstream file(CSV_FILENAME, std::ios::app); // Open file in append mode
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << CSV_FILENAME << std::endl;
        return;
    }

    // Write header if the file is empty
    if (file.tellp() == 0) {
        file << "GameSessionUID,UserID,GameID,StartPoint,EndPoint,DurationInSeconds,Ended\n";
    }

    // Write session data
    file << _gameSessionUID << ","
         << _userID << ","
         << _gameID << ","
         << std::chrono::duration_cast<std::chrono::seconds>(_startPoint.time_since_epoch()).count() << ","
         << (_ended ? std::chrono::duration_cast<std::chrono::seconds>(_endPoint.time_since_epoch()).count() : 0) << ","
         << getDurationInSeconds() << ","
         << _ended << "\n";

    file.close();
}
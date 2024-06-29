#include <sstream>
#include <iostream>
#include "GameSession.hpp"
#include "DataManagerFactory.hpp"


namespace abstract_game {

    GameSession::GameSession(GameID gameID, int userID) :
            _gameSessionUID{calcGameSessionUID()},
            _userID{userID},
            _gameID{gameID},
            _startPoint{std::chrono::steady_clock::now()},
            _ended{false},
            _dataManager{DataManagerFactory::Create("CsvManager")},
            _begin{time(nullptr)} {}

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
        std::string hashInput{ss.str()};

        // create hash from input
        size_t hash{std::hash<std::string>{}(hashInput)};

        return hash;
    }

    void GameSession::increaseRunThroughCount() {
        _runThroughCount++;
    }

    void GameSession::writeToDataManager() const {
        long long startTime = std::chrono::duration_cast<std::chrono::seconds>(_startPoint.time_since_epoch()).count();
        long long endTime = std::chrono::duration_cast<std::chrono::seconds>(_endPoint.time_since_epoch()).count();
        unsigned long long duration{getDurationInSeconds()};

        // size_t sessionUID,
        // int userID,
        // GameID gameID,
        // long long startTime,
        // long long endTime,
        // time_t start,
        // time_t end,
        // bool ended

        _dataManager->saveGameSession(
                _gameSessionUID,
                _userID,
                _gameID,
                startTime,
                endTime,
                _begin,
                _end,
                _ended
        );
        _dataManager->saveRunThroughs(_gameRunThroughs);
    }

    void GameSession::end() {
        _ended = true;

        // save the current time as the end time of the game session
        _endPoint = std::chrono::steady_clock::now();
        _end = time(nullptr);
        writeToDataManager();
    }

    unsigned long long GameSession::getDurationInSeconds() const {
        if (!_ended) {
            // game session is still running
            return std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::steady_clock::now() - _startPoint).count();
        }             // game session has ended
        return std::chrono::duration_cast<std::chrono::seconds>(_endPoint - _startPoint).count();
    }

    void GameSession::addNewGameRunThrough(std::string const &resultUnit, double const &result) {

        increaseRunThroughCount();
        _gameRunThroughs.emplace_back(_gameSessionUID, _runThroughCount, resultUnit, result);
    }

    GameID GameSession::getGameID() const {
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
} // abstract_game
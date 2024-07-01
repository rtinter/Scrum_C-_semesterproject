#include "GameSession.hpp"

#include <iostream>
#include <sstream>

#include "DataManagerFactory.hpp"

namespace abstract_game {
    GameSession::GameSession(GameID const gameID, int const userID) : _gameID{gameID},
                                                                      _userID{userID},
                                                                      _gameSessionUID{calcGameSessionUID()},
                                                                      _begin{time(nullptr)},
                                                                      _end(0),
                                                                      _startPoint{std::chrono::steady_clock::now()},
                                                                      _ended{false},
                                                                      _dataManager{
                                                                          DataManagerFactory::create("CsvManager")
                                                                      } {
    }

    size_t GameSession::calcGameSessionUID() {
        // get current time as string
        std::string const timeString{
            std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
        };

        // get random value as string
        auto const duration{std::chrono::system_clock::now().time_since_epoch()};
        auto const nanos{std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count()};
        std::srand(nanos);
        std::string const randomString{std::to_string(std::rand() % 1000 + 1)};

        // concatenate timeString and random value for hash input
        std::stringstream ss;
        ss << timeString << randomString;
        std::string const hashInput{ss.str()};

        // create hash from input
        size_t const hash{std::hash<std::string>{}(hashInput)};

        return hash;
    }

    void GameSession::increaseRunThroughCount() {
        _runThroughCount++;
    }

    void GameSession::writeToDataManager() const {
        _dataManager->saveGameSession(
            _gameSessionUID,
            _userID,
            _gameID,
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

    void GameSession::addNewGameRunThrough(std::string const &resultUnit, double const &result) {
        increaseRunThroughCount();
        _gameRunThroughs.emplace_back(_gameSessionUID, _runThroughCount, resultUnit, result);
    }
} // abstract_game

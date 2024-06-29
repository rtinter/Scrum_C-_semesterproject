#ifndef ATHENA_GAMESESSION_HPP
#define ATHENA_GAMESESSION_HPP

#include <string>
#include <chrono>
#include <utility>
#include <vector>
#include "GameRunThrough.hpp"
#include "DataManager.hpp"
#include "GameIDs.hpp"
#include "GameRunThroughCsvWriter.hpp"

namespace abstract_game {

/**
 * @brief Class for holding game session information.
 *
 * This class holds information about a game session.
 */
    class GameSession {

        // General information
        GameID _gameID;
        int _userID;

        // Session information
        size_t _gameSessionUID;

        time_t _begin;
        time_t _end;

        std::chrono::steady_clock::time_point _startPoint;
        std::chrono::steady_clock::time_point _endPoint;

        bool _ended;
        std::unique_ptr<DataManager> _dataManager;

        int _runThroughCount{0};
        /**
         * @brief Calculates the game session UID.
         *
         * This method calculates a unique identifier for the game session.
         *
         * @return The game session UID.
         */
        static size_t calcGameSessionUID();

        void increaseRunThroughCount();

        void writeToDataManager() const;

    public:

        std::vector<GameRunThrough> _gameRunThroughs;

        GameSession(GameID gameID, int userID);

        /**
         * @brief Save the current time as the end time of the game session.
         *
         * This method saves the current time as the end time of the game session.
         */
        void end();

        /**
         * @brief Adds a new RunThrough of a game to the vector of Runthroughs of the current session.
         *
         * This method creates a new GameRunThrough that happened during the current Gamesession and adds it to the vector of Runthroughs.
         *
         * @param gameSessionUID the UID of the current gameSession (*this)
         * @param resultUnit the unit in which the result of the game is saved
         * @param result the result of the specific GameRunThrough
         */
        void addNewGameRunThrough(std::string const &resultUnit, long const &result);

    };

} // abstract_game


#endif //ATHENA_GAMESESSION_HPP

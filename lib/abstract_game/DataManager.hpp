#pragma once

#include <vector>

#include "GameIDs.hpp"
#include "GameRunThrough.hpp"

namespace abstract_game {

    /**
     * @brief Abstract base class for managing game data.
     *
     * This class provides an interface for saving game session and run-through data.
     * Concrete implementations of this class will handle specific storage mechanisms.
     */
    class DataManager {
    public:
        virtual ~DataManager() = default;

        /**
         * @brief Save game session information.
         *
         * This method saves the details of a game session.
         *
         * @param sessionUID Unique identifier for the game session.
         * @param userID Identifier for the user.
         * @param gameID Identifier for the game.
         * @param start Timestamp of the session start.
         * @param end Timestamp of the session end.
         * @param ended Boolean indicating if the session has ended.
         */
        virtual void saveGameSession(
            size_t sessionUID,
            int userID,
            GameID gameID,
            time_t start,
            time_t end,
            bool ended
        ) = 0;

        virtual void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) = 0;
    };
} // abstract_game

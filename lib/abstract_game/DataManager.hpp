#pragma once

#include <vector>

#include "GameIDs.hpp"
#include "GameRunThrough.hpp"

namespace abstract_game {
    /**
     * @brief The DataManager class is responsible for saving game session and run-through data.
     *
     * This class defines the interface for saving game session and run-through data.
     * It provides methods for saving game session and run-through data to a specific data storage.
     */
    class DataManager {
    public:
        virtual ~DataManager() = default;

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

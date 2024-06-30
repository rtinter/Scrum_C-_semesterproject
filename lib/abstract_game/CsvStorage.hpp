#pragma once

#include "DataManager.hpp"

namespace abstract_game {
    /**
     * @brief The CsvStorage class is responsible for saving game session and run-through data to CSV files.
     *
     * This class provides methods to save game session and run-through data to CSV files.
     * It handles the logic for writing data to the CSV files and provides methods to retrieve the date string.
     */
    class CsvStorage final : public DataManager {
    public:
        void saveGameSession(
                size_t sessionUID,
                int userID,
                GameID gameID,
                time_t start,
                time_t end,
                bool ended
        ) override;

        static std::string getDateString(time_t timestamp);
        void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) override;
    };

} // abstract_game

#pragma once

#include "DataManager.hpp"

namespace abstract_game {
    /**
     * @brief Class for managing game data using CSV files.
     *
     * This class provides methods to save game session and run-through data into CSV files.
     */
    class CsvStorage final : public DataManager {
    public:
        /**
         * @brief Save game session information to a CSV file.
         *
         * @param sessionUID Unique identifier for the game session.
         * @param userID Identifier for the user.
         * @param gameID Identifier for the game.
         * @param start Timestamp of the session start.
         * @param end Timestamp of the session end.
         * @param ended Boolean indicating if the session has ended.
         */
        void saveGameSession(
            size_t sessionUID,
            int userID,
            GameID gameID,
            time_t start,
            time_t end,
            bool ended
        ) override;

        /**
         * @brief Convert a timestamp to a formatted date string.
         *
         * @param timestamp The timestamp to convert.
         * @return The formatted date string.
         */
        static std::string getDateString(time_t timestamp);

        /**
         * @brief Save run-through data to a CSV file.
         *
         * @param _gameRunThroughs A vector of GameRunThrough objects representing individual game runthroughs.
         */
        void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) override;
    };
} // abstract_game

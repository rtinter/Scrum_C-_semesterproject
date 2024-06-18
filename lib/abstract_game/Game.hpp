#ifndef GAME_H
#define GAME_H

#include "GameSession.hpp"
#include "CsvStorage.hpp"
#include "GameIDs.hpp"
#include <memory>
#include <string>

namespace abstract_game {
/**
 * @brief Abstract base class representing a generic game.
 *
 * This class defines the interface for all specific game implementations.
 * It handles the basic lifecycle of a game, including starting, stopping,
 * and resetting. Additionally, it manages the collection and uploading
 * of game statistics.
 */
    class Game {
    public:
        explicit Game(GameID gameID);

        virtual ~Game() = default;

        /**
         * @brief Renders the game.
         *
         * This method is called by the SceneManager to render the game.
         */
        virtual void render() = 0;


        /**
         * @brief Renders the game.
         *
         * This method is called the in the game to actually render the game.
         */
        virtual void renderGame() = 0;

        /**
         * @brief Starts the game.
         *
         * Begins the game, transitioning it from a ready state to an active state.
         */
        virtual void start() = 0;

        /**
         * @brief Stops the game.
         *
         * Ends the game, transitioning it to a stopped state and uploads the game
         * statistics. Stop calls the reset method.
         */
        virtual void stop();

        /**
         * @brief Resets the game.
         *
         * Resets the game state, preparing it for a new session.
         */
        virtual void reset() = 0;

        virtual std::string getName() const;


        /**
         * @brief Updates the game statistics.
         *
         * This method must be implemented in derived classes and is called to update
         * the statistics, e.g., when a new level is reached or the game ends.
         */
        virtual void updateStatistics() = 0;


    protected:
        std::string _gameName;
        std::string _gameDescription;
        std::string _gameRules;
        std::string _gameControls;

        std::string _endBoxTitle{"Game Over"};
        std::string _endBoxText{"Game Over"};

        bool _showStartBox{true};
        bool _showEndBox{false};
        bool _isGameRunning{false};

        GameID _gameID;

        long _statisticResult;
    };


} //abstract_game

#endif  // GAME_H

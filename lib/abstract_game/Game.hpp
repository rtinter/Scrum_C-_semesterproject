#ifndef GAME_H
#define GAME_H

#include "GameSession.hpp"
#include "CsvStorage.hpp"
#include <string>
#include <chrono>
#include <memory>

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
	Game();
	virtual ~Game() = default;

	/**
	 * @brief Renders the game.
	 *
	 * This method is called by the SceneManager to render the game.
	 */
	virtual void render() =	0;


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

    virtual std::string getName() const = 0;


	/**
	 * @brief Updates the game statistics.
	 *
	 * This method must be implemented in derived classes and is called to update
	 * the statistics, e.g., when a new level is reached or the game ends.
	 */
	virtual void updateStatistics() = 0;


protected:
	const char *_gameName;
	const char *_gameDescription;
	const char *_gameRules;
	const char *_gameControls;

	const char *_endboxTitle {"Game Over"};
	const char *_endboxText {"Game Over"};

	bool _showInfobox{true};
	bool _showEndbox{false};
	bool _isGameRunning{false};

private:

    /**
     * @brief Uploads the game session information.
     *
     * This function handles the logic for uploading the game session information
     * when the game ends or exits.
     */
    void sendSessionInfo();

    /**
     * @brief Saves result of the last RunThrough.
     *
     * This function creates another instance of GameRunThrough that saves the result
     * of the last run of the game and adds it to the current Gamessession.
     * @param resultUnit Unit in which the result is measured.
     * @param result The result of the run.
     */
    void saveRunThroughResult(std::string const &resultUnit, long const &result);

    GameSession _gameSession;

    int _gameID;
};

} // abstract_game

#endif  // GAME_H

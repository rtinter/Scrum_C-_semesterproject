#ifndef GAME_H
#define GAME_H

#include "GameStats.hpp"
#include <string>


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
	Game() = default;
	virtual ~Game() = default;

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
	 * statistics.
	 */
	virtual void stop();

	/**
	 * @brief Resets the game.
	 *
	 * Resets the game state, preparing it for a new session.
	 */
	virtual void reset() = 0;


	/**
	 * @brief Updates the game statistics.
	 *
	 * This method must be implemented in derived classes and is called to update
	 * the statistics, e.g., when a new level is reached or the game ends.
	 */
	virtual void updateStatistics() = 0;

protected:
	/**
	 * @brief Updates a statistic value.
	 *
	 * Derived classes use this method to update the value of a statistic.
	 *
	 * @param name The name of the statistic.
	 * @param value The value of the statistic.
	 */
	void setStatistic(const std::string& name, const long& value);

private:
	/**
	 * @brief Uploads the game results.
	 *
	 * This function handles the logic for uploading the game results when the
	 * game ends or exits.
	 */
	void sendStatistics();

	std::string _gameUUID;
	std::string _gameID;
	std::string _userID;
	GameStats _gameStats;
};

#endif  // GAME_H

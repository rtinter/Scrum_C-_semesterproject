#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <string>
#include <map>

/**
 * @brief Class for managing game statistics.
 *
 * This class allows adding and retrieving statistics, which are stored as
 * name-value pairs. The values are always of type long.
 */
class GameStats {
public:

	/**
	 * @brief Adds or updates a statistic.
	 *
	 * @param name The name of the statistic.
	 * @param value The value of the statistic.
	 */
	void setStatistic(const std::string& name, const long& value);

	/**
	 * @brief Returns all statistics.
	 *
	 * @return A constant reference to the map of statistics.
	 */
	const std::map<std::string, long>& getAllStatistics() const;

	/**
	 * @brief Clears all statistics.
	 */
	void clearStatistics();


    void readFromCsv(const std::string &filename); /// Read statistics from a CSV file.

    void writeToCsv(const std::string &filename) const; /// Write statistics to a CSV file.


private:

	std::map<std::string, long> _statistics;  ///< Map for storing statistics.

};

#endif  // GAME_STATS_H

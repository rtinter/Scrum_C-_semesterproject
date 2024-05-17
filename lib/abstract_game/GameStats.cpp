#include "GameStats.hpp"

void GameStats::setStatistic(const std::string& name, const long& value) {
	statistics[name] = value;
}

const std::map<std::string, long>& GameStats::getAllStatistics() const {
	return statistics;
}

void GameStats::clearStatistics() {
	statistics.clear();
}
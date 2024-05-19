#include "GameStats.hpp"

void GameStats::setStatistic(const std::string& name, const long& value) {
	_statistics[name] = value;
}

const std::map<std::string, long>& GameStats::getAllStatistics() const {
	return _statistics;
}

void GameStats::clearStatistics() {
	_statistics.clear();
}
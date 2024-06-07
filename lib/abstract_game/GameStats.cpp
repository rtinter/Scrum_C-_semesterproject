#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
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

void GameStats::writeToCsv(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    // Write the header
    file << "Name,Value\n";
    // Write each statistic as a row
    for (const auto& stat : _statistics) {
        file << stat.first << "," << stat.second << "\n";
    }
    file.close();
}

void GameStats::readFromCsv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string name;
        std::string valueStr;
        if (std::getline(lineStream, name, ',') &&
            std::getline(lineStream, valueStr)) {
            long value = std::stol(valueStr);
            _statistics[name] = value;
        }
    }
    file.close();
}
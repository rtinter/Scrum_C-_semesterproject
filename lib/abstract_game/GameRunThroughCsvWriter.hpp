#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace abstract_game {
    /**
     * @brief The GameRunThroughCsvWriter class is responsible for writing runthrough data to CSV files.
     *
     * This class provides methods to write runthrough data to CSV files.
     * It handles the logic for writing data to the CSV files and provides methods to retrieve the date string.
     */
    class GameRunThroughCsvWriter {
    public:
        explicit GameRunThroughCsvWriter(std::string const &filename);

        void writeHeader(std::vector<std::string> const &header);

        void writeRow(std::vector<std::string> const &row) {
            for (size_t i{0}; i < row.size(); ++i) {
                _file << row[i];
                if (i != row.size() - 1) {
                    _file << ",";
                }
            }
            _file << "\n";
        }

        void close();

    private:
        std::ofstream _file;
        std::string _filename;
    };
} // abstract_game

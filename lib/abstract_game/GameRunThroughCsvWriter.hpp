#ifndef GameRunThroughCsvWriter_HPP
#define GameRunThroughCsvWriter_HPP

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace abstract_game {

    /**
     * @brief Class for writing game run-through data to a CSV file.
     *
     * The GameRunThroughCsvWriter class provides methods for writing
     * headers and rows of game run-through data to a CSV file. This class
     * handles opening, writing to, and closing the CSV file.
     */
    class GameRunThroughCsvWriter {
    public:
        /**
         * @brief Constructor that opens the CSV file.
         *
         * @param filename The name of the CSV file to open.
         */
        explicit GameRunThroughCsvWriter(std::string const &filename);

        /**
        * @brief Writes the header row to the CSV file.
        *
        * @param header A vector of strings representing the header columns.
        */
        void writeHeader(std::vector<std::string> const &header);

        /**
        * @brief Writes a data row to the CSV file.
        *
        * @param row A vector of strings representing the data columns.
        */
        void writeRow(std::vector<std::string> const &row) {
            for (size_t i {0}; i < row.size(); ++i) {
                _file << row[i];
                if (i != row.size() - 1) {
                    _file << ",";
                }
            }
            _file << "\n";
        }

        /**
         * @brief Closes the CSV file.
         *
         * This method closes the CSV file if it is open.
         */
        void close();

    private:
        std::ofstream _file;
        std::string _filename;
    };


}

#endif // GameRunThroughCsvWriter_HPP

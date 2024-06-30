#ifndef GameRunThroughCsvWriter_HPP
#define GameRunThroughCsvWriter_HPP

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace abstract_game {


    class GameRunThroughCsvWriter {
    public:
        explicit GameRunThroughCsvWriter(std::string const &filename);

        void writeHeader(std::vector<std::string> const &header);

        void writeRow(std::vector<std::string> const &row) {
            for (size_t i {0}; i < row.size(); ++i) {
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


}

#endif // GameRunThroughCsvWriter_HPP

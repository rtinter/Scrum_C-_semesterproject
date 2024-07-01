#include "GameRunThroughCsvWriter.hpp"

#include <stdexcept>

namespace abstract_game {
    GameRunThroughCsvWriter::GameRunThroughCsvWriter(std::string const &filename) : _filename(filename) {
        _file.open(filename, std::ios::app);
        if (!_file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }


    void GameRunThroughCsvWriter::writeHeader(std::vector<std::string> const &header) {
        if (_file.tellp() == 0) {
            // Write header only if file is empty
            for (size_t i{0}; i < header.size(); ++i) {
                _file << header[i];
                if (i != header.size() - 1) {
                    _file << ",";
                }
            }
            _file << "\n";
        }
    }

    void GameRunThroughCsvWriter::close() {
        if (_file.is_open()) {
            _file.close();
        }
    }
} // abstract_game

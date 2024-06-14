//
// Created by Admin on 07.06.2024.
//

#include "GameRunThroughCsvWriter.hpp"
#include <sstream>
#include <iostream>
#include <stdexcept>

namespace abstract_game {

    template<typename T>
    GameRunThroughCsvWriter<T>::GameRunThroughCsvWriter(const std::string &filename) : _filename(filename) {
        _file.open(filename, std::ios::app);
        if (!_file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    template<typename T>
    void GameRunThroughCsvWriter<T>::writeHeader(const std::vector<std::string> &header) {
        if (_file.tellp() == 0) {  // Write header only if file is empty
            for (size_t i = 0; i < header.size(); ++i) {
                _file << header[i];
                if (i != header.size() - 1) {
                    _file << ",";
                }
            }
            _file << "\n";
        }
    }

    template<typename T>
    void GameRunThroughCsvWriter<T>::writeRow(const std::vector<T> &row) {
        for (size_t i = 0; i < row.size(); ++i) {
            _file << row[i];
            if (i != row.size() - 1) {
                _file << ",";
            }
        }
        _file << "\n";
    }

    template<typename T>
    void GameRunThroughCsvWriter<T>::close() {
        if (_file.is_open()) {
            _file.close();
        }
    }
}

// Explicitly instantiate the template for common types (add more as needed)
template class abstract_game::GameRunThroughCsvWriter<int>;
template class abstract_game::GameRunThroughCsvWriter<float>;
template class abstract_game::GameRunThroughCsvWriter<double>;
template class abstract_game::GameRunThroughCsvWriter<std::string>;
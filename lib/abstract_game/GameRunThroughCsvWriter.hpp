//
// Created by Admin on 07.06.2024.
//

#ifndef GameRunThroughCsvWriter_HPP
#define GameRunThroughCsvWriter_HPP

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

namespace abstract_game {

    template<typename T>
    class GameRunThroughCsvWriter {
    public:
        explicit GameRunThroughCsvWriter(const std::string &filename);

        void writeHeader(const std::vector<std::string> &header);

        void writeRow(const std::vector<T> &row);

        void close();

    private:
        std::ofstream _file;
        std::string _filename;
    };

    template<typename T>
    GameRunThroughCsvWriter<T>::GameRunThroughCsvWriter(const std::string &filename) : filename(filename) {
        _file.open(filename, std::ios::app);
        if (!_file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    template<typename T>
    void GameRunThroughCsvWriter<T>::writeHeader(const std::vector<std::string> &header) {
        if (_file.tellp() == 0) {
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

#endif // GameRunThroughCsvWriter_HPP

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


    class GameRunThroughCsvWriter {
    public:
        explicit GameRunThroughCsvWriter(const std::string &filename);

        void writeHeader(const std::vector<std::string> &header);

        template<typename T>
        void writeRow(const std::vector<T> &row);

        void close();

    private:
        std::ofstream _file;
        std::string _filename;
    };


}

#endif // GameRunThroughCsvWriter_HPP

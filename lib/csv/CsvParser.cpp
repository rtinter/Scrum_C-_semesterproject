
#include <iostream>
#include "CsvParser.hpp"

namespace csv {

    std::vector<std::vector<std::string>> CsvParser::parse() {
            std::vector<std::vector<std::string>> data;
        try {
            std::ifstream file(_filename);

            if (!file.is_open()) {
                throw std::runtime_error("Unable to open file: " + _filename);
            }

            std::string line;
            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::string field;
                std::vector<std::string> row;

                while (std::getline(ss, field, ',')) {
                    row.push_back(field);
                }

                data.push_back(row);
            }

            file.close();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        return data;
    }
} // csv
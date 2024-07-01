#pragma once

#include <string>
#include <vector>

namespace csv {
    /*****
     * This class is responsible for parsing a CSV file.
     * It reads the file line by line and splits each line into a vector of strings.
     */
    class CsvParser {
        std::string _filename;

    public:
        explicit CsvParser(std::string const &filename) : _filename(filename) {
        }

        std::vector<std::vector<std::string> > parse() const;
    };
} // csv

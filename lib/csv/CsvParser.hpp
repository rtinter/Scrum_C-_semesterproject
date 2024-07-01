
#ifndef ATHENA_CSVPARSER_H
#define ATHENA_CSVPARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace csv {

    /*****
     * This class is responsible for parsing a CSV file.
     * It reads the file line by line and splits each line into a vector of strings.
     */
    class CsvParser {
        std::string _filename;
    public:
        explicit CsvParser(std::string const &filename) : _filename(filename) {}

        std::vector<std::vector<std::string>> parse();
    };

} // csv

#endif //ATHENA_CSVPARSER_H


#ifndef ATHENA_CSVPARSER_H
#define ATHENA_CSVPARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace csv {

    class CsvParser {
        std::string _filename;
    public:
        explicit CsvParser(const std::string &filename) : _filename(filename) {}

        std::vector<std::vector<std::string>> parse();
    };

} // csv

#endif //ATHENA_CSVPARSER_H

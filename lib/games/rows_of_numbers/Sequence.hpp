#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace rows_of_numbers {
    /*********************************
    * The Sequence class represents a sequence of numbers, its solution,
    * and an explanation for the sequence.
    ***********************************/
    class Sequence {
    public:
        std::string sequence;
        int solution;
        std::string explanation;

        Sequence(std::string const &sequence, int const &solution, std::string const &explanation);

        explicit Sequence(json const &config);
    };
} // rows_of_numbers

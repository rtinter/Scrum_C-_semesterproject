
#ifndef ATHENA_SEQUENCE_HPP
#define ATHENA_SEQUENCE_HPP

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace game {

    class Sequence {
    public:
        std::string sequence;
        int solution;
        std::string explanation;
        Sequence(std::string const &sequence, int const &solution, std::string const &explanation);
        explicit Sequence(json const &config);
    };

} // game

#endif //ATHENA_SEQUENCE_HPP

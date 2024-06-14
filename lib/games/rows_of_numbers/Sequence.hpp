//
// Created by jane on 14.06.24.
//

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
        Sequence(std::string sequence, int solution, std::string explanation);
        Sequence(json& config);
    };

} // game

#endif //ATHENA_SEQUENCE_HPP

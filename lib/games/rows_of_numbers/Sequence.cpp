//
// Created by jane on 14.06.24.
//

#include "Sequence.hpp"

#include <utility>

namespace game {
    Sequence::Sequence(std::string sequence, int solution, std::string explanation) :
        sequence(std::move(sequence)),
        solution(solution),
        explanation(std::move(explanation)) {}

    Sequence::Sequence(json &config) {
        config.at("sequence").get_to(sequence);
        config.at("solution").get_to(solution);
        config.at("explanation").get_to(explanation);
    }
} // game
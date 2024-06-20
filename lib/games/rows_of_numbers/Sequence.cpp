
#include "Sequence.hpp"

#include <utility>

namespace game {
    Sequence::Sequence(std::string const &sequence, int const &solution, std::string const &explanation) :
    sequence(std::move(sequence)),
        solution(solution),
        explanation(std::move(explanation)) {}

    Sequence::Sequence(json const &config) {
        config.at("sequence").get_to(sequence);
        config.at("solution").get_to(solution);
        config.at("explanation").get_to(explanation);
    }
} // game
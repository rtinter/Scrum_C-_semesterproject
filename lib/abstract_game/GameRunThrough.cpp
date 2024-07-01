#include "GameRunThrough.hpp"

namespace abstract_game {
    GameRunThrough::GameRunThrough(size_t const &gameSessionUID,
                                   int const &gameRunThroughUID,
                                   std::string const &resultUnit,
                                   double const &result)
        : gameRunThroughUID{gameRunThroughUID},
          gameSessionUID{gameSessionUID},
          result{result},
          resultUnit{resultUnit} {
    }
} // abstract_game

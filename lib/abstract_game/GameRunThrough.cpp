#include "GameRunThrough.hpp"

namespace abstract_game {


    GameRunThrough::GameRunThrough(size_t const &gameSessionUID,
                                   int const &gameRunThroughUID,
                                   std::string const &resultUnit,
                                   double const &result)
                                   : gameSessionUID{gameSessionUID},
            gameRunThroughUID{gameRunThroughUID},
            resultUnit{resultUnit},
            result{result} {

    }

} // abstract_game
#include "Coordinates.hpp"

namespace commons {
    Coordinates::Coordinates(int const y, int const x) : y(y), x(x) {
    }

    bool Coordinates::operator==(Coordinates const &rhs) const {
        return y == rhs.y && x == rhs.x;
    }

    bool Coordinates::operator!=(Coordinates const &rhs) const {
        return y != rhs.y || x != rhs.x;
    }

    bool Coordinates::operator<(Coordinates const &rhs) const {
        if (y < rhs.y) return true;
        if (rhs.y < y) return false;
        return x < rhs.x;
    }
}

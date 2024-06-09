//
// Created by Benjamin Puhani on 08.06.2024.
//

#include "Coordinates.hpp"

Coordinates::Coordinates(int y, int x) : y(y), x(x) {}

bool Coordinates::operator==(Coordinates const &rhs) const {
    return y == rhs.y && x == rhs.x;
}

bool Coordinates::operator!=(Coordinates const &rhs) const {
    return y != rhs.y || x != rhs.x;
}

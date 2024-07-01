#pragma once

namespace commons {
    /**
     * @brief The Coordinates class represents a coordinate in a 2D plane.
     *
     * This class represents a coordinate in a 2D plane and provides methods for comparing and manipulating coordinates.
     */
    class Coordinates {
    public:
        int y;
        int x;

        Coordinates(int y, int x);

        bool operator==(Coordinates const &rhs) const;

        bool operator!=(Coordinates const &rhs) const;

        bool operator<(Coordinates const &rhs) const;
    };
} // commons

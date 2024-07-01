#include "RandomPicker.hpp"

namespace commons {
    std::random_device RandomPicker::_rd;

    /**
     * @brief Generates a random integer, using a uniform distribution
     * @param min smallest possible integer
     * @param max biggest possible integer
     * @return a random integer between min and max
     */
    int RandomPicker::randomInt(int const &min, int const &max) {
        std::uniform_int_distribution dis(min, max);
        std::mt19937 gen(_rd());
        return dis(gen);
    }
}

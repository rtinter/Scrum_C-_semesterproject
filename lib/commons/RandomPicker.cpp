
#include "RandomPicker.hpp"

namespace commons {

    std::random_device RandomPicker::_rd;

    int RandomPicker::randomInt(int const &min, int const &max) {
        std::uniform_int_distribution<> dis(min, max);
        std::mt19937 gen(_rd());
        return dis(gen);
    }
}

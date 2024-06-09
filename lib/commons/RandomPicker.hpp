#ifndef ATHENA_RANDOMPICKER_H
#define ATHENA_RANDOMPICKER_H

#include <vector>
#include <random>

namespace commons {

    class RandomPicker {
    public:
        RandomPicker() = delete;

        template<typename T>
        static T pickRandomElement(std::vector<T> const &v) {
            std::random_device rd;      // initialize random number generator
            std::mt19937 gen(rd());     // seed Mersenne Twister
            std::uniform_int_distribution<> dis(0, v.size() - 1); // uniform distribution
            return v[dis(gen)];         // return random element from v
        }

    };

} // commons

#endif //ATHENA_RANDOMPICKER_H

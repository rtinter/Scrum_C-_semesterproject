#ifndef ATHENA_RANDOMPICKER_H
#define ATHENA_RANDOMPICKER_H

#include <vector>
#include <random>

namespace commons {

    class RandomPicker {
        static std::random_device _rd;      // initialize random number generator

    public:
        RandomPicker() = delete;

        template<typename T>
        static T pickRandomElement(std::vector<T> const &v) {
            std::mt19937 gen(_rd()); // seed Mersenne Twister
            std::uniform_int_distribution<> dis(0, v.size() - 1); // uniform distribution
            return v[dis(gen)];         // return random element from v
        }

        static int randomInt(const int &min, const int &max);
    };

} // commons

#endif //ATHENA_RANDOMPICKER_H

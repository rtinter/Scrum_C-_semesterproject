#ifndef ATHENA_RANDOMPICKER_H
#define ATHENA_RANDOMPICKER_H

#include <vector>
#include <random>

namespace commons {
    /*****************************************************
    * RandomPicker provides methods to pick random
    * elements from a vector or generate random integers
    *****************************************************/
    class RandomPicker {
        static std::random_device _rd;      // initialize random number generator

    public:
        RandomPicker() = delete; // static class

        /**********************************************************
         * pickRandomElement picks a random element from a vector
         * @tparam T data type of vector elements
         * @param v vector
         * @return a random element from v
         *********************************************************/
        template<typename T>
        static T pickRandomElement(std::vector<T> const &v) {
            std::mt19937 gen(_rd()); // seed Mersenne Twister
            std::uniform_int_distribution<> dis(0, v.size() - 1); // uniform distribution
            return v[dis(gen)];
        }

        static int randomInt(int const &min, int const &max);
    };

} // commons

#endif //ATHENA_RANDOMPICKER_H

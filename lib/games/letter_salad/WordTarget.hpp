#pragma once

#include <string>

namespace letter_salad {
    /**
     * @brief Represents a single word in the game.
     */
    class WordTarget {
        std::string _word;
        mutable bool _found;

    public:
        std::string getWord() const;

        bool *isFound() const;

        void setFound() const;

        explicit WordTarget(std::string const &word);

        bool operator<(WordTarget const &rhs) const;

        WordTarget &operator=(std::string const &word);
    };
} // letter_salad

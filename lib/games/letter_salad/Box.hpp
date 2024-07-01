#pragma once

#include <string>

namespace letter_salad {
    class Box {
        std::string _letter;

    public:
        explicit Box(std::string const &letter);

        bool isSelected{false};
        bool isSolved{false};

        char const *getChar() const;

        std::string getLetter() const;

        void setLetter(std::string const &letter);
    };
} // letter_salad

#include "Box.hpp"

namespace letter_salad {
    char const *Box::getChar() const {
        return _letter.c_str();
    }

    std::string Box::getLetter() const {
        return _letter;
    }

    void Box::setLetter(std::string const &letter) {
        _letter = letter;
    }

    Box::Box(std::string const &letter) {
        _letter = letter;
    }
} // letter_salad

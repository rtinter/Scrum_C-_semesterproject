//
// Created by Benjamin Puhani on 10.06.2024.
//

#include <algorithm>
#include "Box.hpp"
char const *Box::getChar() const {
    return _letter.c_str();
}
std::string Box::getLetter() const {
    return _letter;
}
void Box::setLetter(std::string const &letter) {
    _letter = letter;
    std::transform(_letter.begin(), _letter.end(), _letter.begin(),
                   ::toupper);
}
Box::Box(std::string const &letter) {
    _letter = letter;
}

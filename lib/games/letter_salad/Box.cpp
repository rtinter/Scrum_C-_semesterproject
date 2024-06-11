//
// Created by Benjamin Puhani on 10.06.2024.
//

#include "Box.hpp"
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

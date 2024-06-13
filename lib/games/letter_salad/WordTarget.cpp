//
// Created by Benjamin Puhani (941077) on 11.06.2024.
// &22 Buchstabensalat
//

#include "WordTarget.hpp"
WordTarget::WordTarget(const std::string &word) {
    _word = word;
    _found = false;
}
/**
 * @brief firstly compares the length of the strings.
 * If the length is the same, it defaults to the normal string comparison.
 * (alphabetical order)
 * @param rhs
 * @return
 */
bool WordTarget::operator<(WordTarget const &rhs) const {
    const size_t lhsLength{_word.length()};
    const size_t rhsLength{rhs._word.length()};

    if (lhsLength == rhsLength) {
        // when two strings have the same
        // length, defaults to the normal
        // string comparison
        return (rhs._word < _word);
    }
    return rhsLength < lhsLength;
}
std::string WordTarget::getWord() const {
    return _word;
}
bool *WordTarget::isFound() const {
    return &_found;
}
void WordTarget::setFound() const {
    _found = true;
}

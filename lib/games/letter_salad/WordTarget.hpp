//
// Created by Benjamin Puhani on 11.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_WORDTARGET_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_WORDTARGET_HPP_

#include <string>
class WordTarget {
  std::string _word;
  mutable bool _found;
 public:
  std::string getWord() const;
  bool *isFound() const;
  void setFound() const;
  explicit WordTarget(std::string const &word);
  bool operator<(const WordTarget &rhs) const;
};

#endif //ATHENA_LIB_GAMES_LETTER_SALAD_WORDTARGET_HPP_

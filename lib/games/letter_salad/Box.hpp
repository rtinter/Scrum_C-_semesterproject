//
// Created by benni on 10.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_BOX_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_BOX_HPP_

#include <string>
#include <utility>
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

#endif //ATHENA_LIB_GAMES_LETTER_SALAD_BOX_HPP_

//
// Created by Benjamin Puhani on 08.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_COORDINATES_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_COORDINATES_HPP_

class Coordinates {
 public:
  int y;
  int x;
  Coordinates(int y, int x);
  bool operator==(Coordinates const &rhs) const;
  bool operator!=(Coordinates const &rhs) const;
};

#endif //ATHENA_LIB_GAMES_LETTER_SALAD_COORDINATES_HPP_

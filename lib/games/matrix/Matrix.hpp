//
// Created by reineke on 13.06.24.
//

#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_HPP


#include <array>

class Matrix {
    int static const _SIZE{5};
    int _data[_SIZE][_SIZE];

    Matrix rotate90DegreesRight(int nTimes) const;

    Matrix mirrorHorizontally() const;

    Matrix mirrorVertically() const;

    void render(float cellSize);


public:

    static bool _isClicked;

    void renderBig();

    void renderSmall();

    std::array<Matrix, 2> getAllMirroredVersions() const;

    std::array<Matrix, 3> getAllRotatedVersions() const;

    void init(int nColoredCells);

    int getSize();


};

#endif //ATHENA_MATRIX_HPP

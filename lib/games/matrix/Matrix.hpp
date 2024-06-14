//
// Created by reineke on 13.06.24.
//

#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_HPP


#include <array>

class Matrix {
    int static const _SIZE{5};
    bool _data[_SIZE][_SIZE];

    Matrix rotate90DegreesRight(int nTimes);

    Matrix mirrorHorizontally();

    Matrix mirrorVertically();

public:
    void init();

    void render(float cellSize) const;

    std::array<Matrix, 2> getAllMirroredVersions();

    std::array<Matrix, 3> getAllRotatedVersions();


};

#endif //ATHENA_MATRIX_HPP

//
// Created by reineke on 13.06.24.
//

#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_HPP


#include <array>

class Matrix {
    int static constexpr _SIZE{5};
    float static constexpr _CELL_SIZE_BIG{50.};
    float static constexpr _CELL_SIZE_SMALL{29.};
    int _data[_SIZE][_SIZE];

    Matrix rotate90DegreesRight(int nTimes) const;

    Matrix mirrorHorizontally() const;

    Matrix mirrorVertically() const;

    void render(float cellSize);

    std::array<Matrix, 2> getAllMirroredVersions() const;

    std::array<Matrix, 3> getAllRotatedVersions() const;

public:

    void renderBig();

    void renderSmall();

    void init(int nColoredCells);

    static int getSize();

    static int getCellSizeSmall();

    bool isEqual(Matrix const &other) const;

    bool isMirroredVersionOf(Matrix const &other) const;

    bool isRotatedVersionOf(Matrix const &other) const;

    Matrix getAMirroredVersion() const;

    Matrix getARotatedVersion() const;
};

#endif //ATHENA_MATRIX_HPP

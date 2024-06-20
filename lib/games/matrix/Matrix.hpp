#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_HPP


#include <array>

class Matrix {
    int static constexpr SIZE{5};
    float static constexpr CELL_SIZE_BIG{50.};
    float static constexpr CELL_SIZE_SMALL{29.};
    int _data[SIZE][SIZE];

    Matrix rotate90DegreesRight(int nTimes) const;

    Matrix mirrorHorizontally() const;

    Matrix mirrorVertically() const;

    void render(float cellSize);

    std::array<Matrix, 2> getAllMirroredVersions() const;

    std::array<Matrix, 3> getAllRotatedVersions() const;

    bool isEqual(Matrix const &other) const;

public:

    void renderBig();

    void renderSmall();

    void init(int nCellsWithNumbers);

    static int getSize();

    static int getCellSizeSmall();

    bool isMirroredVersionOf(Matrix const &other) const;

    bool isRotatedVersionOf(Matrix const &other) const;

    Matrix getAMirroredVersion() const;

    Matrix getARotatedVersion() const;
};

#endif //ATHENA_MATRIX_HPP

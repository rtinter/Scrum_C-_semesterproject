#pragma once

#include <array>

namespace matrix {
    /**
     * @brief Models a square matrix and provides functionalities to
     * initialize, render, rotate and mirror it, as well as to compare it
     * to another Matrix object
     */
    class Matrix {
        int static constexpr SIZE{5};
        float static constexpr CELL_SIZE_BIG{50.f};
        float static constexpr CELL_SIZE_SMALL{29.f};
        int _unmarked{-9999};
        int _data[SIZE][SIZE]{};

        Matrix rotate90DegreesRight(int nTimes) const;

        Matrix mirrorHorizontally() const;

        Matrix mirrorVertically() const;

        void render(float cellSize) const;

        std::array<Matrix, 2> getAllMirroredVersions() const;

        std::array<Matrix, 3> getAllRotatedVersions() const;

        bool isEqual(Matrix const &other) const;

    public:
        void renderBig() const;

        void renderSmall() const;

        void init(int nMarkedCells);

        static int getSize();

        static int getCellSizeSmall();

        bool isMirroredVersionOf(Matrix const &other) const;

        bool isRotatedVersionOf(Matrix const &other) const;

        Matrix getAMirroredVersion() const;

        Matrix getARotatedVersion() const;
    };
} // matrix

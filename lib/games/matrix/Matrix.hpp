//
// Created by reineke on 13.06.24.
//

#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_HPP


class Matrix { // TODO: make UiElement?

public:
    int static const _SIZE{5};
    bool _data[_SIZE][_SIZE];

    void init();

    void render(float const cellSize);

    Matrix getRotatedCopy();

    Matrix getMirroredCopy();
};

#endif //ATHENA_MATRIX_HPP

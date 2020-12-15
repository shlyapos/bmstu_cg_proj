#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>

#include "vector3.h"

class Matrix
{
protected:
    std::vector<std::vector<float>> data;
    int rows, cols;

public:
    Matrix(int r = 4, int c = 4);
    Matrix(Vector3f);

    int nrows();
    int ncols();

    std::vector<float>& operator[](const int&);
    Matrix              operator *(const Matrix&);

    void fill(const float&);
    float get(const int&, const int&);

    static Matrix identity(const int&);
    Matrix transpose();
    Matrix inverse();
};


#endif // MATRIX_H

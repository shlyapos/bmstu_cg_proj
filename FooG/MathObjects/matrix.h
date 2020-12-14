#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>

#include "vector3.h"

/*
class Matrix {
protected:
    std::vector<std::vector<float> > m;
    int rows, cols;
public:
    Matrix(int r=4, int c=4);
    Matrix(Vector3f v);
    int nrows();
    int ncols();
    static Matrix identity(int dimensions);
    std::vector<float>& operator[](const int i);
    Matrix operator*(const Matrix& a);
    Matrix transpose();
    Matrix inverse();

    float get(const int&, const int&);
    void fill(const float&);
    //friend std::ostream& operator<<(std::ostream& s, Matrix& m);
};
*/

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

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <memory>

#include "vector3.h"

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

    float get(int i, int j);
    //friend std::ostream& operator<<(std::ostream& s, Matrix& m);
};

/*
class Matrix
{
public:
    Matrix(size_t n = 4, size_t m = 4);
    Matrix(Vector3f);
    Matrix(const Matrix&);

    void fillZero();

    size_t nrows();
    size_t ncols();

    static Matrix identity(size_t);
    Matrix transpose();
    Matrix inverse();


    // Operators
    Matrix& operator =(const Matrix&);
    Matrix& operator =(Matrix&&);
    Matrix operator *(const Matrix&);


    // Methods get/set and row class for operator[][]
    double get(size_t, size_t);
    void set(size_t, size_t, double);

    class MatrixRow
    {
    public:
        MatrixRow(Matrix& m, size_t row) : m(m), row(row) {}
        float& operator [](size_t col)
        {
            return m.data[row][col];
        }
    private:
        Matrix& m;
        size_t row;
    };

    MatrixRow operator [](size_t col)
    {
        return MatrixRow(*this, col);
    }

protected:
    std::vector<std::vector<float>> data;
    size_t n, m;
};
*/

#endif // MATRIX_H

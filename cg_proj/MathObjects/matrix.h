#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
public:
    Matrix();
    Matrix(size_t n, size_t m);

    ~Matrix();

    Matrix& operator =(const Matrix& mtr);
    Matrix& operator =(Matrix&& mtr);

    double get(size_t i, size_t j);
    void set(size_t i, size_t j, double value);

    class MatrixRow
    {
    public:
        MatrixRow(Matrix& m, size_t row) : m(m), row(row) {}
        double& operator [](size_t col)
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
    std::vector<std::vector<double>> data;
};

#endif // MATRIX_H

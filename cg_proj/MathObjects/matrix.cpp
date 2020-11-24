#include "matrix.h"

// Constructors
Matrix::Matrix()
{
    this->data.resize(4);

    for (auto &row : this->data)
    {
        row.resize(4);
    }
}

Matrix::Matrix(size_t n, size_t m)
{
    this->data.resize(n);

    for (auto &row : this->data)
    {
        row.resize(m);
    }
}

// Destructor
Matrix::~Matrix() {}


// Equal
Matrix& Matrix::operator =(const Matrix& mtr)
{
    this->data = mtr.data;
    return *this;
}

Matrix& Matrix::operator =(Matrix&& mtr)
{
    this->data = mtr.data;
    return *this;
}


// Get/Set methods
double Matrix::get(size_t i, size_t j)
{
    return this->data[i][j];
}

void Matrix::set(size_t i, size_t j, double value)
{
    this->data[i][j] = value;
}

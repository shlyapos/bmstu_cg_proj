#include "geometry.h"

// Constructors
Matrix::Matrix(size_t n, size_t m)
{
    this->n = n;
    this->m = m;

    this->data.resize(n);

    for (size_t i = 0; i < n; i++)
    {
        this->data[i].resize(m);
    }

    fillZero();
}

Matrix::Matrix(Vector3f v)
{
    this->n = 4;
    this->m = 1;

    this->data.resize(n);

    for (size_t i = 0; i < n; i++)
    {
        this->data[i].resize(m);
    }

    fillZero();

    this->data[0][0] = v.x;
    this->data[1][0] = v.y;
    this->data[2][0] = v.z;
}

Matrix::Matrix(const Matrix& newM)
{
    this->n = newM.n;
    this->m = newM.m;

    this->data = newM.data;
}



void Matrix::fillZero()
{
    for (size_t i = 0; i < this->n; i++)
    {
        for (size_t j = 0; j < this->m; j++)
        {
            this->data[i][j] = 0;
        }
    }
}



size_t Matrix::nrows()
{
    return this->n;
}

size_t Matrix::ncols()
{
    return this->m;
}



Matrix Matrix::identity(size_t dimensions)
{
    Matrix e(dimensions, dimensions);

    for (size_t i = 0; i < dimensions; i++)
    {
        for (size_t j = 0; j < dimensions; j++)
        {
            e[i][j] = (i == j ? 1.f : 0.f);
        }
    }

    return e;
}

Matrix Matrix::transpose()
{
    Matrix result(this->n, this->m);

    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->m; j++)
            result[j][i] = this->data[i][j];

    return result;
}

Matrix Matrix::inverse()
{
    // Warning!!! this bastard is wanted by the police

    // A little optimization
    size_t rows = this->n;
    size_t cols = this->m;
    size_t i, j, k;

    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(rows, cols * 2);

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            result[i][j] = data[i][j];

    for(i = 0; i < rows; i++)
        result[i][i + cols] = 1;

    // first pass
    for (i = 0; i < (rows - 1); i++)
    {
        // normalize the first row
        for(j = (result.m - 1); j >= 0; j--)
            result[i][j] /= result[i][i];

        for (k = (i + 1); k < rows; k++)
        {
            float coeff = result[k][i];

            for (j = 0; j < result.m; j++)
                result[k][j] -= result[i][j] * coeff;
        }
    }

    // normalize the last row
    for(j = result.m - 1; j >= (rows - 1); j--)
        result[rows - 1][j] /= result[rows - 1][rows - 1];

    // second pass
    for (i = (rows - 1); i > 0; i--)
    {
        for (k = (i - 1); k >= 0; k--)
        {
            float coeff = result[k][i];

            for (j = 0; j < result.m; j++)
                result[k][j] -= (result[i][j] * coeff);
        }
    }

    // cut the identity matrix back
    Matrix truncate(rows, cols);

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            truncate[i][j] = result[i][j + cols];

    return truncate;
}



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

Matrix& Matrix::operator *(const Matrix& a)
{
    size_t rows = this->n;
    size_t cols = this->m;

    Matrix result(rows, a.m);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < a.m; j++)
        {
            result.data[i][j] = 0.f;

            for (size_t k = 0; k < cols; k++)
            {
                result.data[i][j] += this->data[i][k] * a.data[k][j];
            }
        }
    }

    return result;
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

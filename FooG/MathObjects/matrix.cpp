#include "matrix.h"

// Constructors
Matrix::Matrix(Vector3f v)
    : data(std::vector<std::vector<float>>(4, std::vector<float>(1, 1.f))), rows(4), cols(1)
{
    data[0][0] = v.x;
    data[1][0] = v.y;
    data[2][0] = v.z;
}


Matrix::Matrix(const int r, int c)
    : data(std::vector<std::vector<float>>(r, std::vector<float>(c, 0.f))), rows(r), cols(c)
{

}



int Matrix::nrows()
{
    return rows;
}

int Matrix::ncols()
{
    return cols;
}



// Operators
std::vector<float>& Matrix::operator[](const int& i)
{
    return data[i];
}

Matrix             Matrix::operator *(const Matrix& a)
{
    Matrix result(rows, a.cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            result.data[i][j] = 0.0f;

            for (int k = 0; k < rows; k++)
                result.data[i][j] += data[i][k] * a.data[k][j];
        }
    }

    return result;
}



void Matrix::fill(const float& v)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = v;
}

float Matrix::get(const int& i, const int& j)
{
    return data[i][j];
}



// Create a new identity matrix of size dimensions
Matrix Matrix::identity(const int& dimensions)
{
    Matrix result(dimensions, dimensions);

    for (int i = 0; i < dimensions; i++)
        for (int j = 0; j < dimensions; j++)
            result[i][j] = (i == j ? 1.f : 0.f);

    return result;
}

Matrix Matrix::transpose()
{
    Matrix result(cols, rows);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            result[j][i] = data[i][j];

    return result;
}


// Scary function, boo...
Matrix Matrix::inverse()
{
    // Just little optimization
    int i, j, k;

    // augmenting the square matrix with the identity matrix of the same dimensions a => [ai]
    Matrix result(rows, cols*2);

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            result[i][j] = data[i][j];

    for(i = 0; i < rows; i++)
        result[i][i + cols] = 1;

    // first pass
    for (i = 0; i < (rows - 1); i++)
    {
        // normalize the first row
        for(j = (result.cols - 1); j >= 0; j--)
            result[i][j] /= result[i][i];

        for (k = (i + 1); k < rows; k++)
        {
            float coeff = result[k][i];

            for (j = 0; j < result.cols; j++)
                result[k][j] -= result[i][j]*coeff;
        }
    }

    // normalize the last row
    for(j = (result.cols - 1); j >= (rows - 1); j--)
        result[rows - 1][j] /= result[rows - 1][rows - 1];

    // second pass
    for (i = (rows - 1); i > 0; i--)
    {
        for (k = (i - 1); k >= 0; k--)
        {

            float coeff = result[k][i];

            for (j = 0; j < result.cols; j++)
                result[k][j] -= result[i][j] * coeff;
        }
    }

    // cut the identity matrix back
    Matrix truncate(rows, cols);

    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            truncate[i][j] = result[i][j + cols];

    return truncate;
}

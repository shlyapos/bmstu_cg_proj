#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#include <memory>

class Matrix;


template<class t>
class Vector3
{
public:
    t x, y, z;
    t w = 1;

    Vector3<t>() : x(t()), y(t()), z(t())
    {

    }
    Vector3<t>(t x, t y, t z) : x(x), y(y), z(z)
    {

    }
    Vector3<t>(Matrix m)
    {
        this->x = m[0][0] / m[3][0];
        this->y = m[1][0] / m[3][0];
        this->z = m[2][0] / m[3][0];
    }
    Vector3<t>(const Vector3<t>& v)
    {
        *this = v;
    }

    template<class u> Vector3<t>(const Vector3<u>& v);


    // Operators
    Vector3<t>& operator =(const Vector3<t>& v)
    {
        if (this != &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }
        return *this;
    }

    Vector3<t>  operator +(const Vector3<t>& v) const
    {
        return Vector3<t>(x + v.x, y + v.y, z + v.z);
    }
    Vector3<t>  operator -(const Vector3<t>& v) const
    {
        return Vector3<t>(x - v.x, y - v.y, z - v.z);
    }
    t           operator *(const Vector3<t>& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }


    // Other interesting operators
    Vector3<t>  operator ^(const Vector3<t>& v) const
    {
        return Vector3<t>(y * v.z - z * v.y,
                          z * v.x - x * v.z,
                          x * v.y - y * v.x);
    }
    Vector3<t>  operator *(float f) const
    {
        return Vector3<t>(x * f, y * f, z * f);
    }
    t&          operator[](const int i)
    {
        if (i <= 0)
            return x;
        else if (i == 1)
            return y;
        else
            return z;
    }


    // Other methods
    float norm() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3<t>& normalize(t l = 1)
    {
        *this = (*this) * (l / norm());
        return *this;
    }

    void transform(const std::shared_ptr<Matrix> matrix);
};

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;

template <> template <> Vector3<int>::Vector3(const Vector3<float> &v);
template <> template <> Vector3<float>::Vector3(const Vector3<int> &v);


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
    Matrix& operator *(const Matrix&);


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

#endif // GEOMETRY_H

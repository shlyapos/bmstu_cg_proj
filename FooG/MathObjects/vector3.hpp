#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "vector3.h"

// Constructors
template<class t>
Vector3<t>::Vector3() : x(t()), y(t()), z(t()), w(1)
{

}

template<class t>
Vector3<t>::Vector3(t x, t y, t z, t w) : x(x), y(y), z(z), w(w)
{

}

template<class t>
Vector3<t>::Vector3(Matrix m) : x(m[0][0] / m[3][0]), y(m[1][0] / m[3][0]), z(m[2][0] / m[3][0]), w(1)
{

}



// Operators
template<class t>
Vector3<t>& Vector3<t>::operator =(const Vector3<t>& v)
{
    if (this != &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    return *this;
}

template<class t>
Vector3<t>  Vector3<t>::operator +(const Vector3<t>& v) const
{
    return Vector3<t>(x + v.x, y + v.y, z + v.z);
}

template<class t>
Vector3<t>  Vector3<t>::operator -(const Vector3<t>& v) const
{
    return Vector3<t>(x - v.x, y - v.y, z - v.z);
}

template<class t>
t           Vector3<t>::operator *(const Vector3<t>& v) const
{
    return x * v.x + y * v.y + z * v.z;
}



// Other interesting operators
template<class t>
Vector3<t>  Vector3<t>::operator ^(const Vector3<t>& v) const
{
    return Vector3<t>(y * v.z - z * v.y,
                      z * v.x - x * v.z,
                      x * v.y - y * v.x);
}

template<class t>
Vector3<t>  Vector3<t>::operator *(const float& f) const
{
    return Vector3<t>(x * f, y * f, z * f);
}

template<class t>
t&          Vector3<t>::operator[](const int& idx)
{
    if (idx <= 0)
        return x;
    else if (idx == 1)
        return y;
    else if (idx == 2)
        return z;
    else
        return w;
}



// Other methods
template<class t>
float Vector3<t>::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template<class t>
Vector3<t>& Vector3<t>::normalize(t l)
{
    *this = (*this) * (l / norm());
    return *this;
}

template<class t>
void Vector3<t>::transform(const std::shared_ptr<Matrix> matrix)
{
    std::vector<float> result(4);
    std::vector<float> data = { this->x, this->y, this->z, this->w };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix->get(i, j);
        }
    }

    this->x = result[0];
    this->y = result[1];
    this->z = result[2];
}

#endif // VECTOR3_HPP

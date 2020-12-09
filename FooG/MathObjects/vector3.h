#ifndef VECTOR3_H
#define VECTOR3_H

#include <memory>
#include <cmath>
#include <vector>

#define TO_RAD_180 180

class Matrix;

template<class t>
class Vector3
{
public:
    t x, y, z;
    t w = 1;

    Vector3<t>();
    Vector3<t>(t x, t y, t z);
    Vector3<t>(Matrix m);
    Vector3<t>(const Vector3<t>& v);

    template<class u> Vector3<t>(const Vector3<u>& v);


    // Operators
    Vector3<t>& operator =(const Vector3<t>& v);
    Vector3<t>  operator +(const Vector3<t>& v) const;
    Vector3<t>  operator -(const Vector3<t>& v) const;
    t           operator *(const Vector3<t>& v) const;


    // Other interesting operators
    Vector3<t>  operator ^(const Vector3<t>& v) const;
    Vector3<t>  operator *(float f) const;
    t&          operator[](const int i);


    // Other methods
    float norm() const;
    Vector3<t>& normalize(t l = 1);
    void transform(const std::shared_ptr<Matrix> matrix);
};


using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;


template <> template <> Vector3<int>::Vector3(const Vector3<float> &v);
template <> template <> Vector3<float>::Vector3(const Vector3<int> &v);

#include "matrix.h"

#endif // VECTOR3_H

#ifndef VECTOR3_H
#define VECTOR3_H

#include <memory>
#include <cmath>
#include <vector>

#define TO_RAD_180 180
#define EPS 1e-6

class Matrix;

template<class t>
class Vector3
{
public:
    t x, y, z, w;

    Vector3<t>();
    Vector3<t>(t, t, t, t w = 1);
    Vector3<t>(Matrix);

    template<class u> Vector3<t>(const Vector3<u>&);


    // Operators
    Vector3<t>& operator =(const Vector3<t>&);
    Vector3<t>  operator +(const Vector3<t>&) const;
    Vector3<t>  operator -(const Vector3<t>&) const;
    t           operator *(const Vector3<t>&) const;


    // Other interesting operators
    Vector3<t>  operator ^(const Vector3<t>&) const;
    Vector3<t>  operator *(const float&) const;
    t&          operator[](const int&);


    // Other methods
    float norm() const;
    Vector3<t>& normalize(t l = 1);
    void transform(const std::shared_ptr<Matrix>);
};


using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;


template <> template <> Vector3<int>::Vector3(const Vector3<float>&);
template <> template <> Vector3<float>::Vector3(const Vector3<int>&);

#include "matrix.h"

#endif // VECTOR3_H

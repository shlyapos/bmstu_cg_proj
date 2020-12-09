#include "vector3.h"

template <> template <> Vector3<int>::Vector3(const Vector3<float> &v)
{
    this->x = static_cast<int>(v.x + 0.5f);
    this->y = static_cast<int>(v.y + 0.5f);
    this->z = static_cast<int>(v.z + 0.5f);
}

template <> template <> Vector3<float>::Vector3(const Vector3<int> &v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}


#include "vector2.h"

template<> template<> Vector2<int>::Vector2(Vector2<float>& v)
{
    this->x = static_cast<int>(v.X() + 0.5f);
    this->y = static_cast<int>(v.Y() + 0.5f);
}

template<> template<> Vector2<float>::Vector2(Vector2<int> &v)
{
    this->x = static_cast<float>(v.X());
    this->y = static_cast<float>(v.Y());
}

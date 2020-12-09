#ifndef VECTOR2_H
#define VECTOR2_H

template<class t> class Vector2
{
public:
    Vector2<t>() : x(t()), y(t())       { }
    Vector2<t>(t x, t y) : x(x), y(y)   { }

    Vector2<t>(const Vector2<t>& v) : x(t()), y(t()) { *this = v; }

    template<class u> Vector2<t>(Vector2<u>& v);

    Vector2<t>& operator =(const Vector2<t>& v)
    {
        if (this != &v)
        {
            x = v.x;
            y = v.y;
        }
        return *this;
    }
    Vector2<t>& operator +(const Vector2<t>& v) const
    {
        return Vector2<t>(x + v.x, y + v.y);
    }
    Vector2<t>& operator -(const Vector2<t>& v) const
    {
        return Vector2<t>(x - v.x, y - v.y);
    }
    Vector2<t>& operator *(float f) const
    {
        return Vector2<t>(x * f, y * f);
    }

    t X() { return this->x; }
    void X(t newX) { this->x = newX; }

    t Y() { return this->y; }
    void Y(t newY) { this->y = newY; }

private:
    t x, y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;

template<> template<> Vector2<int>::Vector2(Vector2<float>& v);
template<> template<> Vector2<float>::Vector2(Vector2<int> &v);

#endif // VECTOR2_H

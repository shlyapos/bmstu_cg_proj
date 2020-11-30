#include "triangle.h"

Triangle::Triangle() : a(Point()), b(Point()), c(Point())
{

}


Triangle::Triangle(Point& A, Point& B, Point& C) : a(A), b(B), c(C)
{

}

Vector Triangle::getTriangleNormal()
{
    Vector v1(a, b);
    Vector v2(b, c);

    Vector vn = v1.cross(v2);
    vn.normalize();

    return vn;
}

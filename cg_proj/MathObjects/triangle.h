#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "vector.h"

class Triangle
{
public:
    Triangle();
    Triangle(Point& A, Point& B, Point& C);

    Vector getTriangleNormal();

private:
    Point a;
    Point b;
    Point c;

    Vector normal;
};

#endif // TRIANGLE_H

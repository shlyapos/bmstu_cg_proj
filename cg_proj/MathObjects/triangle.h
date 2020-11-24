#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle
{
public:
    Triangle();
    Triangle(Point& A, Point& B, Point& C);

private:
    Point a;
    Point b;
    Point c;
};

#endif // TRIANGLE_H

#ifndef POINT_H
#define POINT_H

#include <memory>

#include "matrix.h"

class Point
{
public:
    // Constructor
    Point();
    Point(double x, double y, double z);

    Point(const Point& pnt);
    Point(Point&& pnt);

    // Destructor
    ~Point();

    // Operators equal
    Point& operator =(const Point& pnt);
    Point& operator =(Point&& pnt);

    // Addition
    Point operator +(const Point& pnt) const;
    Point& operator +=(const Point& pnt);

    // Subtraction
    Point operator -(const Point& pnt) const;
    Point& operator -=(const Point& pnt);

    // Multiplication
    Point operator *(const Point& pnt) const;
    Point& operator *=(const Point& pnt);

    // Division
    Point operator /(const Point& pnt) const;
    Point& operator /=(const Point& pnt);

    // Getters
    double getX();
    double getY();
    double getZ();

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    void transform(const std::shared_ptr<Matrix> matrix);

private:
    double x;
    double y;
    double z;
    double w = 1;
};

#endif // POINT_H

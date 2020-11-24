#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

#include "point.h"
#include "matrix.h"

class Vector
{
public:
    // Constructor
    Vector();
    Vector(double x, double y, double z);
    Vector(Point p1, Point p2);

    // Destructor
    ~Vector();

    // Methods
    void normalize();
    double length();
    void transform(Matrix matrix);
    void addVector(Vector v);

    // Operators
    Vector& operator =(const Vector& v);
    const Vector operator +(const Vector& v) const;
    const Vector operator -(const Vector& v) const;
    const Vector operator *(const double src) const;

private:
    double x;
    double y;
    double z;
    double w;
};

#endif // VECTOR_H

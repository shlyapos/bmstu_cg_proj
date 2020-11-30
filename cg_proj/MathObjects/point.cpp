#include "point.h"

// Constructors
Point::Point() : x(0), y(0), z(0)
{

}

Point::Point(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ)
{

}

Point::Point(const Point& pnt)
{
    this->x = pnt.x;
    this->y = pnt.y;
    this->z = pnt.z;
}

Point::Point(Point&& pnt)
{
    this->x = pnt.x;
    this->y = pnt.y;
    this->z = pnt.z;
}


// Destructor
Point::~Point()
{

}


// Operators equal
Point& Point::operator =(const Point& pnt)
{
    this->x = pnt.x;
    this->y = pnt.y;
    this->z = pnt.z;

    return *this;
}

Point& Point::operator =(Point&& pnt)
{
    this->x = pnt.x;
    this->y = pnt.y;
    this->z = pnt.z;

    return *this;
}


// Additions
Point Point::operator +(const Point& pnt) const
{
    Point result = Point(*this);

    result.x += pnt.x;
    result.y += pnt.y;
    result.z += pnt.z;

    return result;
}

Point& Point::operator +=(const Point& pnt)
{
    this->x += pnt.x;
    this->y += pnt.y;
    this->z += pnt.z;

    return *this;
}


// Subtraction
Point Point::operator -(const Point& pnt) const
{
    Point result = Point(*this);

    result.x -= pnt.x;
    result.y -= pnt.y;
    result.z -= pnt.z;

    return result;
}

Point& Point::operator -=(const Point& pnt)
{
    this->x -= pnt.x;
    this->y -= pnt.y;
    this->z -= pnt.z;

    return *this;
}


// Multiplication
Point Point::operator *(const Point& pnt) const
{
    Point result = Point(*this);

    result.x *= pnt.x;
    result.y *= pnt.y;
    result.z *= pnt.z;

    return result;
}

Point& Point::operator *=(const Point& pnt)
{
    this->x *= pnt.x;
    this->y *= pnt.y;
    this->z *= pnt.z;

    return *this;
}


// Division
Point Point::operator /(const Point& pnt) const
{
    Point result = Point(*this);

    result.x /= pnt.x;
    result.y /= pnt.y;
    result.z /= pnt.z;

    return result;
}

Point& Point::operator /=(const Point& pnt)
{
    this->x /= pnt.x;
    this->y /= pnt.y;
    this->z /= pnt.z;

    return *this;
}


// Getters
double Point::getX()
{
    return this->x;
}

double Point::getY()
{
    return this->y;
}

double Point::getZ()
{
    return this->z;
}


// Setters
void Point::setX(double newX)
{
    this->x = newX;
}

void Point::setY(double newY)
{
    this->y = newY;
}

void Point::setZ(double newZ)
{
    this->z = newZ;
}


void Point::transform(const std::shared_ptr<Matrix> matrix)
{
    std::vector<double> result(4);
    std::vector<double> data = { this->x, this->y, this->z, this->w };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix->get(i, j);
        }
    }

    *this = { result[0], result[1], result[2] };
}

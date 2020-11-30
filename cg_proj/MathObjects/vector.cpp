#include "vector.h"

#define EPS 0.0001

// Constructors
Vector::Vector()
{

}

Vector::Vector(Point p1, Point p2)
{
    this->x = p2.getX() - p1.getX();
    this->y = p2.getY() - p1.getY();
    this->z = p2.getZ() - p1.getZ();
}


// Destructor
Vector::~Vector() {}


// Other methods
void Vector::normalize()
{
    double length = this->length();

    if (length < EPS || length > -EPS)
    {
        this->x /= length;
        this->y /= length;
        this->z /= length;
    }
}

double Vector::length()
{
    double length = sqrt(this->x * this->x +
                         this->y * this->y +
                         this->z + this->z);
    return length;
}

void Vector::transform(Matrix matrix)
{
    std::vector<double> result(4);
    std::vector<double> data = { this->x, this->y, this->z, this->w };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix[i][j];
        }
    }

    *this = { result[0], result[1], result[2] };
}


// Operators
Vector& Vector::operator =(const Vector& v)
{
    if (this == &v)
    {
        return *this;
    }

    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;

    return *this;
}

const Vector Vector::operator +(const Vector &v) const
{
    double tmpX = this->x + v.x;
    double tmpY = this->y + v.y;
    double tmpZ = this->z + v.z;

    return Vector(tmpX, tmpY, tmpZ);
}

const Vector Vector::operator -(const Vector &v) const
{
    double tmpX = this->x - v.x;
    double tmpY = this->y - v.y;
    double tmpZ = this->z - v.z;

    return Vector(tmpX, tmpY, tmpZ);
}

const Vector Vector::operator *(const double value) const
{
    double tmpX = this->x * value;
    double tmpY = this->y * value;
    double tmpZ = this->z * value;

    return Vector(tmpX, tmpY, tmpZ);
}

Vector Vector::cross(Vector v)
{
    Vector result;

    result.x = this->y * v.z - this->z * v.y;
    result.y = this->z * v.x - this->x * v.z;
    result.z = this->x * v.y - this->y * v.x;

    return result;
}

double Vector::crossScalar(Vector v)
{
    return (this->x * v.x + this->y * v.y + this->z * v.z);
}

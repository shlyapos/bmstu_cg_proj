#include "transformmatrix.h"

MoveMatrix::MoveMatrix(int x, int y, int z)
{
    this->data[0][0] = 1;
    this->data[1][1] = 1;
    this->data[2][2] = 1;
    this->data[3][3] = 1;

    this->data[0][3] = x;
    this->data[1][3] = y;
    this->data[2][3] = z;
}


RotateOxMatrix::RotateOxMatrix(double angle)
{
    this->data[0][0] = 1;
    this->data[1][1] = cos(angle);
    this->data[1][2] = -sin(angle);
    this->data[2][1] = sin(angle);
    this->data[2][2] = cos(angle);
    this->data[3][3] = 1;
}

RotateOyMatrix::RotateOyMatrix(double angle)
{
    this->data[0][0] = cos(angle);
    this->data[1][1] = 1;
    this->data[2][0] = -sin(angle);
    this->data[0][2] = sin(angle);
    this->data[2][2] = cos(angle);
    this->data[3][3] = 1;
}

RotateOzMatrix::RotateOzMatrix(double angle)
{
    this->data[0][0] = cos(angle);
    this->data[0][1] = -sin(angle);
    this->data[1][0] = sin(angle);
    this->data[1][1] = cos(angle);
    this->data[2][2] = 1;
    this->data[3][3] = 1;
}

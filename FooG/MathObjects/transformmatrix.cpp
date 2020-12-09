#include "transformmatrix.h"

MoveMatrix::MoveMatrix(int x, int y, int z)
{
    this->m[0][0] = 1;
    this->m[1][1] = 1;
    this->m[2][2] = 1;
    this->m[3][3] = 1;

    this->m[0][3] = x;
    this->m[1][3] = y;
    this->m[2][3] = z;
}


RotateOxMatrix::RotateOxMatrix(double angle)
{
    this->m[0][0] = 1;
    this->m[1][1] = cos(angle);
    this->m[1][2] = -sin(angle);
    this->m[2][1] = sin(angle);
    this->m[2][2] = cos(angle);
    this->m[3][3] = 1;
}

RotateOyMatrix::RotateOyMatrix(double angle)
{
    this->m[0][0] = cos(angle);
    this->m[1][1] = 1;
    this->m[2][0] = -sin(angle);
    this->m[0][2] = sin(angle);
    this->m[2][2] = cos(angle);
    this->m[3][3] = 1;
}

RotateOzMatrix::RotateOzMatrix(double angle)
{
    this->m[0][0] = cos(angle);
    this->m[0][1] = -sin(angle);
    this->m[1][0] = sin(angle);
    this->m[1][1] = cos(angle);
    this->m[2][2] = 1;
    this->m[3][3] = 1;
}
/*
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
*/

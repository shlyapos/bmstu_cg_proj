#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "matrix.h"
#include <math.h>

class MoveMatrix : public Matrix
{
public:
    MoveMatrix(int x, int y, int z);
};


class RotateOxMatrix : public Matrix
{
public:
    RotateOxMatrix(double angle);
};

class RotateOyMatrix : public Matrix
{
public:
    RotateOyMatrix(double angle);
};

class RotateOzMatrix : public Matrix
{
public:
    RotateOzMatrix(double angle);
};

#endif // TRANSFORMMATRIX_H

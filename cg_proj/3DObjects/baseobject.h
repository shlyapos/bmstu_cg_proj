#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "../MathObjects/point.h"

class BaseObject
{
public:
    BaseObject();

    void move();

    void rotateX();
    void rotateY();
    void rotateZ();
};

#endif // BASEOBJECT_H

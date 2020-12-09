#ifndef CAMERA_H
#define CAMERA_H

#include "MathObjects/vector3.h"
#include "MathObjects/vector3.hpp"

class Camera
{
public:
    Camera();

    Vector3f getPosition();
    void setPosition(Vector3f v);

    Vector3f getDirection();
    void setDirection(Vector3f v);

    void turn(Vector3f v);
    void move(Vector3f v);

private:
    Vector3f position;
    Vector3f direction;
};

#endif // CAMERA_H

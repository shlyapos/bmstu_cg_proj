#include "camera.h"

Camera::Camera()
{
    this->position = Vector3f(0, 0, -1);
    this->direction = Vector3f(0, 0, 0);
}


// Position
Vector3f Camera::getPosition()
{
    return this->position;
}

void Camera::setPosition(Vector3f v)
{
    this->position = v;
}


// Direction
Vector3f Camera::getDirection()
{
    return this->direction;
}

void Camera::setDirection(Vector3f v)
{
    this->direction = v;
}


// Transforms
void Camera::turn(Vector3f v)
{
    this->direction.x += v.x;
    this->direction.y += v.y;
    this->direction.z += v.z;
}

void Camera::move(Vector3f v)
{
    this->position.x += v.x;
    this->position.y += v.y;
    this->position.z += v.z;
}

#include "camera.h"

Camera::Camera() : xAngle(0), yAngle(0), zAngle(0)
{
    position = Point(0, 0, -1000);
}


// Position
const Point& Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(const Point &position)
{
    this->position = position;
}

void Camera::setPosition(Point position)
{
    this->position.setX(position.getX());
    this->position.setY(position.getY());
    this->position.setZ(position.getZ());
}


// Angles
double Camera::getXAngle()
{
    return xAngle;
}

void Camera::setXAngle(double newXAngle)
{
    this->xAngle = newXAngle;
}


double Camera::getYAngle()
{
    return yAngle;
}

void Camera::setYAngle(double newYAngle)
{
    this->yAngle = newYAngle;
}


double Camera::getZAngle()
{
    return zAngle;
}

void Camera::setZAngle(double newZAngle)
{
    this->zAngle = newZAngle;
}


void Camera::transformCamera(const std::shared_ptr<Matrix> matrix)
{
    this->position.transform(matrix);
}

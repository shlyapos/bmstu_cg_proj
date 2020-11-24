#ifndef CAMERA_H
#define CAMERA_H

#include "MathObjects/matrix.h"
#include "MathObjects/point.h"

class Camera
{
public:
    Camera();

    const Point& getPosition() const;
    void setPosition(const Point& position);
    void setPosition(Point position);

    double getXAngle();
    void setXAngle(double newXAngle);

    double getYAngle();
    void setYAngle(double newYAngle);

    double getZAngle();
    void setZAngle(double newZAngle);

    void transformCamera(const std::shared_ptr<Matrix> matrix);

private:
    Point position;
    double xAngle;
    double yAngle;
    double zAngle;
};

#endif // CAMERA_H

#ifndef LIGHTSOURCEPOINT_H
#define LIGHTSOURCEPOINT_H

#include "MathObjects/vector3.h"

#define LIGHT_REFLECT 1
#define BG_LIGHT 0.3

class LightSourcePoint
{
public:
    LightSourcePoint(float i, Vector3f p);

    Vector3f getPosition();
    void setPosition(Vector3f v);

    float getIntensity();

private:
    float i;

    Vector3f position;
};

#endif // LIGHTSOURCEPOINT_H

#include "lightsourcepoint.h"

LightSourcePoint::LightSourcePoint(float i, Vector3f p)
{
    // Bug light position
    p.y *= -1;

    this->i = i;
    this->position = p;
}


Vector3f LightSourcePoint::getPosition()
{
    return this->position;
}

void LightSourcePoint::setPosition(Vector3f v)
{
    this->position = v;
}


float LightSourcePoint::getIntensity()
{
    return this->i;
}

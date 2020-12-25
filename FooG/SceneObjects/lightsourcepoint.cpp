#include "lightsourcepoint.h"

// Constructors
LightSourcePoint::LightSourcePoint(const Vector3f& pos, const float& p) : position(pos), power(p)
{

}



// Position methods
Vector3f& LightSourcePoint::getPosition()
{
    return position;
}

void      LightSourcePoint::setPosition(const Vector3f& newPos)
{
    position = newPos;
}



// Intensity methods
float LightSourcePoint::getIntensity()
{
    return power;
}

void  LightSourcePoint::setIntensity(const float& newPower)
{
    power = newPower;
}

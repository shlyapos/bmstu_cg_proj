#ifndef LIGHTSOURCEPOINT_H
#define LIGHTSOURCEPOINT_H

#include "../MathObjects/vector3.h"

#define LIGHT_REFLECT 1
#define BG_LIGHT 0.3

class LightSourcePoint
{
private:
    Vector3f position;
    float power;

public:
    LightSourcePoint(const Vector3f& pos = Vector3f(0, 0, 0), const float& power = 500);

    Vector3f& getPosition();
    void      setPosition(const Vector3f&);

    float getIntensity();
    void  setIntensity(const float&);
};

#endif // LIGHTSOURCEPOINT_H

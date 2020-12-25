#ifndef SPRITE_H
#define SPRITE_H

#include "model.h"

class Sprite : public Model
{
private:
    Vector3f start;
    Vector3f end;
    Vector3f speed;

    bool isReached;

public:
    Sprite(const char*, const QColor&, const Vector3f& center = Vector3f(0, 0, 0));

    void setPath(const Vector3f&, const float&);
    void updatePath();
    bool isReachedEnd();

    Vector3f getStart();
    void setStart(const Vector3f&);

    Vector3f getEnd();
    void setEnd(const Vector3f&);

    float getSpeed();
    void setSpeed(const float&);
};

#endif // SPRITE_H

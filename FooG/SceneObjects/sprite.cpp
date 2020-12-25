#include "sprite.h"

#include <QDebug>

Sprite::Sprite(const char* file, const QColor& color, const Vector3f& center)
    : Model(file, color, center)
{
    this->isSprite = true;
}



void Sprite::setPath(const Vector3f& e, const float& newSpeed)
{
    end = e;
    setSpeed(newSpeed);

    isReached = false;
}

void Sprite::updatePath()
{
    center.x += speed.x;
    center.y += speed.y;
    center.z += speed.z;

    qDebug() << center.x << center.y << center.z;

    if (fabs(center.x - end.x) < EPS &&
        fabs(center.y - end.y) < EPS &&
        fabs(center.z - end.z) < EPS)
        isReached = true;
}

bool Sprite::isReachedEnd()
{
    return isReached;
}


Vector3f Sprite::getStart()
{
    return start;
}

void Sprite::setStart(const Vector3f& newS)
{
    start = newS;
}



Vector3f Sprite::getEnd()
{
    return end;
}

void Sprite::setEnd(const Vector3f& newE)
{
    end = newE;
}



float Sprite::getSpeed()
{
    if (speed.x != 0)
        return fabs(speed.x);
    else if (speed.y != 0)
        return fabs(speed.y);
    else
        return fabs(speed.z);
}

void Sprite::setSpeed(const float& newSpeed)
{
    float x = 0;
    float y = 0;
    float z = 0;

    if (end.x != center.x)
        x = center.x < end.x ? newSpeed : -newSpeed;

    if (end.y != center.y)
        y = center.y < end.y ? newSpeed : -newSpeed;

    if (end.z != center.z)
        z = center.z < end.z ? newSpeed : -newSpeed;

    speed = Vector3f(x, y, z);
}

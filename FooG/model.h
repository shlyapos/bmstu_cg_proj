#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <QColor>

#include "MathObjects/vector3.h"
#include "MathObjects/vector3.hpp"

class Model
{
private:
    std::vector<Vector3f> verts;
    // attention, this Vec3i means vertex/uv/normal
    std::vector<std::vector<Vector3i>> faces;
    std::vector<Vector3f> norms;

    QColor color;

public:
    Model(const char *filename, QColor& color);
    ~Model();

    int getVertsCount();
    int getFacesCount();

    QColor getColor();

    void scale(float k);
    void doScale();

    Vector3f vert(int index);
    std::vector<int> face(int index);
    Vector3f norm(int iface, int nvert);
};

#endif // MODEL_H

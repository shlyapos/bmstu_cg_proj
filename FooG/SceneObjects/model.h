#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <QColor>

#include "../MathObjects/vector3.h"
#include "../MathObjects/vector3.hpp"

#include "../MathObjects/transformmatrix.h"

class Model
{
protected:
    Vector3f center;
    std::vector<Vector3f> verts;

    // attention, this Vector3i means vertex/uv/normal
    std::vector<std::vector<Vector3i>> faces;
    std::vector<Vector3f> norms;

    QColor color;

    Vector3f normalCalculate(const Vector3f&, const Vector3f&, const Vector3f&);
    void normalsProcessing();

    bool isSprite = false;

public:
    Model(const char*, const QColor&, const Vector3f& center = Vector3f(0, 0, 0));

    // Center
    Vector3f& getCenter();
    void      setCenter(const Vector3f&);

    // Vertes
    int       getVertsCount();
    Vector3f& vert(const int&);

    // Faces
    int              getFacesCount();
    std::vector<int> face(const int&);

    // Normals
    int       getNormsCount();
    void      setNorm(const int&, const int&, const Vector3f&);
    Vector3f& norm(const int&, const int&);

    // Color
    QColor& getColor();
    void    setColor(const QColor&);

    void scale(const Vector3f&);
    void rotate(const Vector3f&);
};

#endif // MODEL_H

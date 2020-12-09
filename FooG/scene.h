#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "camera.h"
#include "lightsourcepoint.h"
#include "MathObjects/transformmatrix.h"

class Scene
{
public:
    Scene();

    void addModel(Model newModel);
    Model& getModel(int index);

    void addLightPoint(float i, Vector3f lp);
    LightSourcePoint& getLightPoint(int idx);
    size_t getLightsCount();

    Camera& getCamera()
    {
        return this->mainCamera;
    };

    void cameraTurn(Vector3f v);
    void cameraMove(Vector3f v);

    int size();

private:
    std::vector<Model> models;
    Camera mainCamera;

    std::vector<LightSourcePoint> lightPoint;

};

#endif // SCENE_H

#ifndef SCENE_H
#define SCENE_H

#include "model.h"
#include "camera.h"
#include "lightsourcepoint.h"

class Scene
{
private:
    Camera mainCamera;
    std::vector<Model> models;
    std::vector<LightSourcePoint> lightSources;

public:
    Scene();

    // Models
    void   addModel(const Model&, const Vector3f& scale = Vector3f(1, 1, 1));
    Model& getModel(const int&);
    int    countModels();

    // Lights
    void              addLightSource(const Vector3f&, const float&);
    LightSourcePoint& getLightSource(const int&);
    int               getLightSourceCount();

    // Camera
    //Camera& getCamera();
    Camera&   getCamera();
    void      setCamera(const Vector3f&, const Vector3f&, const Vector3f&);

    Vector3f& getCameraPos();
    Vector3f& getCameraView();
    Vector3f& getCameraUp();

    void      upDownCamera(const float&);
    void      rotateCamera(const float&);
    void      strafeCamera(const float&);
    void      movingCamera(const float&);
};

#endif // SCENE_H

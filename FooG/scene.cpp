#include "scene.h"

#include <QDebug>

#define EPS 1e-6

// Constructors
Scene::Scene()
    : mainCamera(Camera()), models(std::vector<Model>()), lightSources(std::vector<LightSourcePoint>())
{

}



// Models
void   Scene::addModel(const Model& newModel)
{
    models.push_back(newModel);
}

Model& Scene::getModel(const int& idx)
{
    return models[idx];
}

int    Scene::countModels()
{
    return models.size();
}



// Lights
void Scene::addLightSource(const Vector3f& lPos, const float& lPower)
{
    lightSources.push_back(LightSourcePoint(lPos, lPower));
}

LightSourcePoint& Scene::getLightSource(const int& idx)
{
    return lightSources[idx];
}

int Scene::getLightSourceCount()
{
    return lightSources.size();
}



// Camera methods
Camera&   Scene::getCamera()
{
    return mainCamera;
}

void      Scene::setCamera(const Vector3f& pos, const Vector3f& view, const Vector3f& up)
{
    mainCamera = Camera(pos, view, up);
}



Vector3f& Scene::getCameraPos()
{
    return mainCamera.getPosition();
}

Vector3f& Scene::getCameraView()
{
    return mainCamera.getView();
}

Vector3f& Scene::getCameraUp()
{
    return mainCamera.getUp();
}



void    Scene::upDownCamera(const float& speed)
{
    Vector3f pos = mainCamera.getPosition();

    if (abs(1.25 - pos.y) > EPS || abs(-1.25 + pos.y) > EPS)
        mainCamera.upDown(speed);
}

void    Scene::rotateCamera(const float& speed)
{
    mainCamera.rotateView(speed);
}

void    Scene::strafeCamera(const float& speed)
{
    mainCamera.update();
    mainCamera.strafe(speed);
}

void    Scene::movingCamera(const float& speed)
{
    mainCamera.move(speed);
}

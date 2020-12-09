#include "scene.h"

#include <QDebug>

Scene::Scene()
{

}

int Scene::size()
{
    return this->models.size();
}

void Scene::addModel(Model newModel)
{
    this->models.push_back(newModel);
}

Model& Scene::getModel(int index)
{
    return this->models[index];
}


void Scene::addLightPoint(float i, Vector3f lp)
{
    LightSourcePoint newLp(i, lp);
    this->lightPoint.push_back(newLp);
}

LightSourcePoint& Scene::getLightPoint(int idx)
{
    return this->lightPoint[idx];
}

size_t Scene::getLightsCount()
{
    return this->lightPoint.size();
}


void Scene::cameraTurn(Vector3f v)
{
    this->mainCamera.turn(v);
}

void Scene::cameraMove(Vector3f v)
{
    Vector3f position = this->mainCamera.getPosition();
    Vector3f direction = this->mainCamera.getDirection();

    std::shared_ptr<Matrix> r1(new RotateOxMatrix(-direction.x * M_PI / 180));
    position.transform(r1);

    std::shared_ptr<Matrix> r2(new RotateOxMatrix(-direction.y * M_PI / 180));
    position.transform(r2);

//    std::shared_ptr<Matrix> r3(new RotateOxMatrix(-direction.z * M_PI / 180));
//    position.transform(r3);

    this->mainCamera.setPosition(position);
    this->mainCamera.move(v);

    qDebug() << this->mainCamera.getPosition().x << this->mainCamera.getPosition().y << this->mainCamera.getPosition().z;
}

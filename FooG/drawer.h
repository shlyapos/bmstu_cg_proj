#ifndef DRAWER_H
#define DRAWER_H

#include <QImage>
#include <QGraphicsScene>

#include <cmath>
#include "MathObjects/matrix.h"

#include "zbuffer.h"
#include "scene.h"

class Drawer : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Drawer(QObject *parent = nullptr);
    ~Drawer();

    void initZBuffer(int width, int height);
    void initImage(QImage image);

    void drawScene();

    void cameraTurn(Vector3f v);
    void cameraMove(Vector3f v);

    QColor getBGColor();

private:
    // ********************
    Vector3f center = Vector3f(0, 0, 0);
    Vector3f eye = Vector3f(1,1,3);

    Matrix viewport(int x, int y, int w, int h);
    void lookat(Vector3f eye, Vector3f center, Vector3f up);
    // ********************

    int w;
    int h;

    ZBuffer zbuffer;
    Scene scene;

    std::vector<std::vector<QColor>> colorCache;
    QImage image;

    void triangleProcessing(Vector3i t0, Vector3i t1, Vector3i t2, QColor col, float i0, float i1, float i2);
    void drawObjects(Model& model);

    Vector3f getProjection(const Vector3f& vert);
    float getIntensity(const Vector3f& vert, Vector3f norm);

    void fillFromCache();
    void clearScene();
    void clearColorCache();
    void clearZbuffer();

    QColor bgColor = QColor(50, 50, 50);
};

#endif // DRAWER_H

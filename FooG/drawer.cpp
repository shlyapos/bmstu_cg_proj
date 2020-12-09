#include "drawer.h"
#include <QDebug>
#include <QRgb>

#define DEPTH 255

// ********************************************************************************************* //
Matrix ModelView(4, 4);

Matrix Drawer::viewport(int x, int y, int w, int h) {
    Matrix m = Matrix::identity(4);
    m[0][3] = x+w/2.f;
    m[1][3] = y+h/2.f;
    m[2][3] = DEPTH/2.f;

    m[0][0] = w/2.f;
    m[1][1] = h/2.f;
    m[2][2] = DEPTH/2.f;
    return m;
}

void Drawer::lookat(Vector3f eye, Vector3f center, Vector3f up) {
    Vector3f z = (scene.getCamera().getPosition()-center).normalize();
    Vector3f x = (up ^ z).normalize();
    Vector3f y = (z ^ x).normalize();
    Matrix Minv = Matrix::identity(4);
    Matrix Tr   = Matrix::identity(4);
    for (int i=0; i<3; i++) {
        Minv[0][i] = x[i];
        Minv[1][i] = y[i];
        Minv[2][i] = z[i];
        Tr[i][3] = -center[i];
    }
    ModelView = Minv*Tr;
}
// ********************************************************************************************* //

// Very smart function, meh...
inline QRgb i_color(QRgb a, float i)
{
    QColor c(a);
    int r, g, b;

    c.getRgb(&r, &g, &b);

    r *= i; g *= i; b *= i;

    if (r > 255)
        r = 255;
    else if (r < 0)
        r = 0;
    if (g > 255)
        g = 255;
    else if (g < 0)
        g = 0;
    if (b > 255)
        b = 255;
    else if (b < 0)
        b = 0;

    c.setRgb(r, g, b);

    return c.rgba();
}


Drawer::Drawer(QObject *parent) : QGraphicsScene (parent)
{
    this->scene = Scene();

    QColor color = Qt::red;
    this->scene.addModel(Model("hand.obj", color));

    color = Qt::green;
    //this->scene.addModel(Model("plane.obj", color));

    this->scene.addLightPoint(500, Vector3f(0, -100, -100));
}

Drawer::~Drawer()
{

}


// Draw scene objects by triangles
void Drawer::triangleProcessing(Vector3i t0, Vector3i t1, Vector3i t2,
                                QColor col, float i0, float i1, float i2)
{
    if (t0.y==t1.y && t0.y==t2.y)
        return;
    if (t0.y>t1.y)
    {
        std::swap(t0, t1);
        std::swap(i0, i1);
    }
    if (t0.y>t2.y)
    {
        std::swap(t0, t2);
        std::swap(i0, i2);
    }
    if (t1.y>t2.y)
    {
        std::swap(t1, t2);
        std::swap(i1, i2);
    }

    int total_height = t2.y - t0.y;

    for (int i=0; i<total_height; i++)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;

        float alpha = (float)i / total_height;
        float betta  = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;

        Vector3i A =               t0 + Vector3f(t2 - t0) * alpha;
        Vector3i B = second_half ? t1 + Vector3f(t2 - t1) * betta : t0 + Vector3f(t1 - t0) * betta;

        float iA =               i0 + (i2 - i0) * alpha;
        float iB = second_half ? i1 + (i2 - i1) * betta : i0 + (i1 - i0) * betta;

        if (A.x>B.x)
        {
            std::swap(A, B);
            std::swap(iA, iB);
        }

        for (int j = A.x; j <= B.x; j++)
        {
            float phi = B.x == A.x ? 1. : (float)(j - A.x) / (float)(B.x - A.x);

            Vector3i P = Vector3f(A) + Vector3f(B - A) * phi;
            float iP = iA + (iB - iA) * phi;

            if (P.x >= this->w || P.y >= this->h || P.x < 0 || P.y < 0) continue;

            if (zbuffer.getDepth(P.x, P.y) < P.z)
            {
                zbuffer.setDepth(P.x, P.y, P.z);
                colorCache[P.x][P.y] = QColor(i_color(col.rgba(), iP));
            }
        }
    }
}

void Drawer::drawObjects(Model& model)
{
    lookat(eye, center, Vector3f(0,1,0));
    Matrix Projection = Matrix::identity(4);
    Matrix ViewPort   = viewport(w/8, h/8, w*3/4, h*3/4);
    Projection[3][2] = -1.f/(eye-center).norm();

    //Matrix z(ViewPort * Projection * ModelView);

    for (int i = 0; i < model.getFacesCount(); i++)
    {
        std::vector<int> face = model.face(i);

        Vector3f screenCoords[3];
        Vector3f world_coords[3];

        float intensity[3];

        for (int j=0; j<3; j++)
        {
            Vector3f v = model.vert(face[j]);
            screenCoords[j] = Vector3f(ViewPort*Projection*ModelView*Matrix(v));
            getProjection(screenCoords[j]);
            //world_coords[j]  = v;

            intensity[j] = getIntensity(screenCoords[j], model.norm(i, j));

            //intensity[j] = model->norm(i, j)*light_dir;
        }

        triangleProcessing(screenCoords[0], screenCoords[1], screenCoords[2],
                model.getColor(), intensity[0], intensity[1], intensity[2]);
    }
    /*
    int depth = 255;

    for (int i=0; i < model.getFacesCount(); i++)
    {
        std::vector<int> face = model.face(i);

        Vector3f screenCoords[3];
        //Vector3f world_coords[3];

        float intensity[3];

        for (int j = 0; j < 3; j++)
        {
            Vector3f v = model.vert(face[j]);//getProjection(model.vert(face[j]));

            screenCoords[j] = Vector3f((v.x + 1.) * w / 2.,
                                       (v.y + 1.) * h / 2.,
                                       (v.z + 1.) * depth / 2.);

            screenCoords[j] = getProjection(screenCoords[j]);
            //world_coords[j]  = v;

            intensity[j] = getIntensity(v, model.norm(i, j));
        }

        triangleProcessing(screenCoords[0], screenCoords[1], screenCoords[2],
                model.getColor(), intensity[0], intensity[1], intensity[2]);
    }
    */
}

Vector3f Drawer::getProjection(const Vector3f& vert)
{
    Vector3f cameraPos = this->scene.getCamera().getPosition();
    Vector3f cameraDir = this->scene.getCamera().getDirection();

    Vector3f res = vert;

    std::shared_ptr<Matrix> m1(new MoveMatrix(-cameraPos.x, -cameraPos.y, -cameraPos.z));
    res.transform(m1);

    std::shared_ptr<Matrix> r1(new RotateOxMatrix(cameraDir.x * M_PI / 180));
    res.transform(r1);

    std::shared_ptr<Matrix> r2(new RotateOyMatrix(cameraDir.y * M_PI / 180));
    res.transform(r2);

    std::shared_ptr<Matrix> r3(new RotateOyMatrix(cameraDir.z * M_PI / 180));
    res.transform(r3);

    return res;
}

float Drawer::getIntensity(const Vector3f& vert, Vector3f norm)
{
    size_t nlight = this->scene.getLightsCount();

    float intensity = 0;

    for (size_t i = 0; i < nlight; i++)
    {
        LightSourcePoint lsp = this->scene.getLightPoint(i);

        Vector3f lightDir = vert - lsp.getPosition();

        intensity += lightDir * norm / pow(lightDir.norm(), 2.0);
        intensity *= lsp.getIntensity() * LIGHT_REFLECT;

        intensity = fmax(0.0, intensity);
        intensity = fmin(1.0, intensity);

        intensity = BG_LIGHT + intensity * (1 - BG_LIGHT);
    }

    return intensity;
}

void Drawer::drawScene()
{
    clearScene();

    for (int i = 0; i < scene.size(); i++)
    {
        drawObjects(scene.getModel(i));
    }

    QImage img = QImage(w + 1, h + 1, QImage::Format_RGB32);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            img.setPixelColor(i, h - j, colorCache[i][j]);
        }
    }

    this->addPixmap(QPixmap::fromImage(img));
}


// Initialization some stuff
void Drawer::initZBuffer(int width, int height)
{
    this->w = width;
    this->h = height;

    this->zbuffer = ZBuffer(width, height);

    this->zbuffer.clearZBuffer();
}

void Drawer::initImage(QImage image)
{
    int w = image.width();
    int h = image.height();

    this->image = image;
    this->colorCache.resize(w);

    for (int i = 0; i < w; i++)
    {
        this->colorCache[i].resize(h);

        for (int j = 0; j < h; j++)
        {
            this->colorCache[i][j] = bgColor;
        }
    }
}


// Screen processing
void Drawer::fillFromCache()
{
    for (int i = 0; i < this->w; i++)
    {
        for (int j = 0; j < this->h; j++)
        {
            this->image.setPixelColor(i, this->h - j, colorCache[i][j]);
        }
    }

    this->addPixmap(QPixmap::fromImage(image));
}

void Drawer::clearScene()
{
    clearColorCache();
    clearZbuffer();
}

void Drawer::clearColorCache()
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            colorCache[i][j] = bgColor;
        }
    }
}

void Drawer::clearZbuffer()
{
    this->zbuffer.clearZBuffer();
}


QColor Drawer::getBGColor()
{
    return this->bgColor;
}


// Main camera processing
void Drawer::cameraTurn(Vector3f v)
{
    //this->eye = eye + v;
    this->scene.cameraTurn(v);
}

void Drawer::cameraMove(Vector3f v)
{
    //this->eye = eye + v;
    this->scene.cameraMove(v);
}

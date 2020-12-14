#include "drawer.h"

#include <QDebug>

// Very smart function, meh...
inline QRgb iColor(const QRgb& a, const float& i)
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


// Public methods
Drawer::Drawer(const int& w, const int& h, QObject *parent)
    : QGraphicsScene(parent), w(w), h(h)
{
    initCanvas();
    initColorCache();
    initZBuffer();

    scene.setCamera(Vector3f(0, 0, -10), Vector3f(0, 0, 0), Vector3f(0, 1, 0));
    scene.addLightSource(Vector3f(0, -10, 0), 100);

    scene.addModel(Model("cube.obj", Qt::red, Vector3f(10, 0, 0)));
    scene.addModel(Model("cube.obj", Qt::red, Vector3f(8, 0, 0)));

    updateCanvas();
    updateScreen();
}

Drawer::~Drawer()
{

}


// Draw objects
void Drawer::draw()
{
    clearScreen();

    size_t models = scene.countModels();

    Vector3f camPos = scene.getCameraPos();
    Vector3f camDir = scene.getCameraView();
    Vector3f camUp  = scene.getCameraUp();

    for (size_t i = 0; i < models; i++)
    {
        objectProcessing(scene.getModel(i), camPos, camDir, camUp);
    }

    updateCanvas();
    updateScreen();
}


// Camera
void Drawer::upDownCamera(const float& speed)
{
    scene.upDownCamera(speed);
}

void Drawer::rotateCamera(const float& speed)
{
    scene.rotateCamera(speed);
}

void Drawer::strafeCamera(const float& speed)
{
    scene.strafeCamera(speed);
}

void Drawer::movingCamera(const float& speed)
{
    scene.movingCamera(speed);
}



// Private methods
// Main draw processing methods
void Drawer::objectProcessing(Model& model, Vector3f& camPos, Vector3f& camDir, Vector3f& camUp)
{
    size_t i, j;

    size_t   faces  = model.getFacesCount();
    Vector3f center = model.getCenter();
    QColor   color  = model.getColor();

    //Transformation matrix (not sure how it works)
    Matrix viewPort   = Camera::viewport(0, 0, w, h);
    Matrix projection = Matrix::identity(4);
    Matrix modelView  = Camera::lookAt(camPos, camDir, camUp);

    projection[3][2]  = - 1.f / (camPos - camDir).norm();

    Matrix mvp = viewPort * projection * modelView;

    for (i = 0; i < faces; i++)
    {
        std::vector<int> face = model.face(i);

        Vector3i screenCoords[3];
        float    intensity[3];

        for (j = 0; j < 3; j++)
        {
            Vector3f v = center + model.vert(face[j]);

            screenCoords[j] = Vector3f(mvp * Matrix(v));
            intensity[j] = lightProcessing(v, model.norm(i, j));
        }

        triangleProcessing(screenCoords[0], screenCoords[1], screenCoords[2],
                color, intensity[0], intensity[1], intensity[2]);
    }
}

float Drawer::lightProcessing(const Vector3f& vert, const Vector3f& norm)
{
    size_t lights = scene.getLightSourceCount();
    float intensity = 0;

    for (size_t i = 0; i < lights; i++)
    {
        LightSourcePoint lsp = scene.getLightSource(i);

        Vector3f lightDir = vert - lsp.getPosition();

        intensity += lightDir * norm / pow(lightDir.norm(), 2.0);
        intensity *= lsp.getIntensity() * LIGHT_REFLECT;

        intensity = fmax(0.0, intensity);
        intensity = fmin(1.0, intensity);

        intensity = BG_LIGHT + intensity * (1 - BG_LIGHT);
    }

    return intensity;
}

void Drawer::triangleProcessing(Vector3i& t0, Vector3i& t1, Vector3i& t2,
                                const QColor& color, float& i0, float& i1, float& i2)
{
    if (t0.y == t1.y && t0.y == t2.y)
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

    for (int i = 0; i < total_height; i++)
    {
        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;

        float alpha = (float)i / total_height;
        float betta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;

        Vector3i A =               t0 + Vector3f(t2 - t0) * alpha;
        Vector3i B = second_half ? t1 + Vector3f(t2 - t1) * betta : t0 + Vector3f(t1 - t0) * betta;

        float iA =               i0 + (i2 - i0) * alpha;
        float iB = second_half ? i1 + (i2 - i1) * betta : i0 + (i1 - i0) * betta;

        if (A.x > B.x)
        {
            std::swap(A, B);
            std::swap(iA, iB);
        }

        //if (A.x >= w || A.y >= h || A.x < 0 || A.y < 0) continue;
        //if (B.x >= w || B.y >= h || B.x < 0 || B.y < 0) continue;

        A.x = std::max(A.x, 0);
        B.x = std::min(B.x, w);

        for (int j = A.x; j <= B.x; j++)
        {
            float phi = B.x == A.x ? 1. : (float)(j - A.x) / (float)(B.x - A.x);

            Vector3i P = Vector3f(A) + Vector3f(B - A) * phi;
            float iP = iA + (iB - iA) * phi;

            if (P.x >= w || P.y >= h || P.x < 0 || P.y < 0) continue;

            if (zBuffer.getDepth(P.x, P.y) < P.z)
            {
                zBuffer.setDepth(P.x, P.y, P.z);
                colorCache[P.x][P.y] = QColor(iColor(color.rgba(), iP));
            }
        }
    }


}


Matrix Drawer::viewport(const int& x, const int& y, const int& w, const int& h)
{
    Matrix m = Matrix::identity(4);

    m[0][3] = x + w / 2.0f;
    m[1][3] = y + h / 2.0f;
    m[2][3] = DEPTH / 2.0f;

    m[0][0] = w / 2.0f;
    m[1][1] = h / 2.0f;
    m[2][2] = DEPTH / 2.0f;

    return m;
}


// Screen
void Drawer::initCanvas()
{
    canvas = QImage(w + 1, h + 1, QImage::Format_RGB32);
}

void Drawer::clearCanvas()
{
    canvas.fill(bgColor);
}

void Drawer::updateCanvas()
{
    for (int i = 0; i < w + 1; i++)
    {
        for (int j = 0; j < h + 1; j++)
        {
            canvas.setPixelColor(i, j, colorCache[i][j]);
        }
    }
}


// Z-Buffer
void Drawer::initZBuffer()
{
    zBuffer = ZBuffer(w + 1, h + 1);
}

void Drawer::clearZBuffer()
{
    zBuffer.clearZBuffer();
}


// Color cache
void Drawer::initColorCache()
{
    colorCache = std::vector<std::vector<QColor>>(w + 1, std::vector<QColor>(h + 1, bgColor));
}

void Drawer::clearColorCache()
{
    for (int i = 0; i < w + 1; i++)
    {
        for (int j = 0; j < h + 1; j++)
        {
            colorCache[i][j] = bgColor;
        }
    }
}


// Screen
void Drawer::updateScreen()
{
    this->addPixmap(QPixmap::fromImage(canvas));
}

void Drawer::clearScreen()
{
    clearCanvas();
    clearColorCache();
    clearZBuffer();
}

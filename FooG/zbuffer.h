#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <QColor>

#include <limits>
#include <vector>

class ZBuffer
{
public:
    ZBuffer();
    ZBuffer(int width, int height);

    void clearZBuffer();
    void fillColors();

    int width();
    int height();

    void setDepth(int x, int y, int value);
    int getDepth(int x, int y);

private:
    int w;
    int h;

    std::vector<std::vector<int>> data;

    int background = std::numeric_limits<int>::min();
};

#endif // ZBUFFER_H

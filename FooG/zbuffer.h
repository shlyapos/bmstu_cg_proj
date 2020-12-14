#ifndef ZBUFFER_H
#define ZBUFFER_H

#include <limits>
#include <vector>

class ZBuffer
{
private:
    int w, h;
    std::vector<std::vector<int>> data;
    int background = std::numeric_limits<int>::min();

public:
    ZBuffer();
    ZBuffer(const int&, const int&);

    int width();
    int height();

    void clearZBuffer();

    void setDepth(const int&, const int&, const int&);
    int  getDepth(const int&, const int&);
};

#endif // ZBUFFER_H

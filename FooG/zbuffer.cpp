#include "zbuffer.h"

// Constructor
ZBuffer::ZBuffer() : w(0), h(0), data(std::vector<std::vector<int>>())
{

}

ZBuffer::ZBuffer(const int& w, const int& h)
    : w(w), h(h), data(std::vector<std::vector<int>>(w, std::vector<int>(h, background)))
{

}



int ZBuffer::width()
{
    return w;
}

int ZBuffer::height()
{
    return h;
}



void ZBuffer::clearZBuffer()
{
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
             data[i][j] = background;
}



void ZBuffer::setDepth(const int& x, const int& y, const int& value)
{
    data[x][y] = value;
}

int  ZBuffer::getDepth(const int& x, const int& y)
{
    return data[x][y];
}

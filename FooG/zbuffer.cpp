#include "zbuffer.h"

ZBuffer::ZBuffer() : w(0), h(0)
{

}

ZBuffer::ZBuffer(int width, int height)
{
    this->w = width;
    this->h = height;

    this->data.resize(width);

    for (int i = 0; i < width; i++)
    {
        this->data[i].resize(height);
    }
}


void ZBuffer::clearZBuffer()
{
    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
             this->data[i][j] = background;
}


void ZBuffer::setDepth(int x, int y, int value)
{
    this->data[x][y] = value;
}

int ZBuffer::getDepth(int x, int y)
{
    return this->data[x][y];
}

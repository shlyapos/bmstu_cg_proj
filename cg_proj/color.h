#ifndef COLOR_H
#define COLOR_H

#include <QColor>

class Color : public QColor
{
public:
    // Constructor
    Color();
    Color(QColor c);
    Color(double R, double G, double B, int a);

    Color& operator =(const Color& newColor);
    const Color operator +(const Color& v) const;
    const Color operator -(const Color& v) const;
    const Color operator *(const double value) const;
};

#endif // COLOR_H

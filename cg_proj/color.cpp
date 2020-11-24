#include "color.h"

// Constructor
Color::Color()
{

}

Color::Color(QColor c)
{
    this->setRed(c.red());
    this->setGreen(c.green());
    this->setBlue(c.blue());
    this->setAlpha(c.alpha());
}

Color::Color(double R, double G, double B, int a)
{
    this->setRed(R);
    this->setGreen(G);
    this->setBlue(B);
    this->setAlpha(a);
}


// Operators
Color& Color::operator =(const Color& newColor)
{
    if (this == &newColor)
    {
        return *this;
    }

    this->setAlpha(255);

    this->setRed(newColor.red());
    this->setGreen(newColor.green());
    this->setBlue(newColor.blue());

    return *this;
}

const Color Color::operator +(const Color& newColor) const
{
    return Color(this->red() + newColor.red(),
                 this->green() + newColor.green(),
                 this->blue() + newColor.blue(), 255);
}

const Color Color::operator -(const Color& newColor) const
{
    return Color(this->red() - newColor.red(),
                 this->green() - newColor.green(),
                 this->blue() - newColor.blue(), 255);
}

const Color Color::operator *(const double value) const
{
    return Color(this->red() * value,
                 this->green() * value,
                 this->blue() * value, 255);
}

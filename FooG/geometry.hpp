#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "geometry.h"

template<class t>
void Vector3<t>::transform(const std::shared_ptr<Matrix> matrix)
{
    std::vector<float> result(4);
    std::vector<float> data = { this->x, this->y, this->z, this->w };

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result[i] += data[j] * matrix->get(i, j);
        }
    }

    this->x = result[0];
    this->y = result[1];
    this->z = result[2];
}

#endif // GEOMETRY_HPP

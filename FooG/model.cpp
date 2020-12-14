#include "model.h"

Model::Model(const char *filename, const QColor& color, const Vector3f& center)
    : center(center), color(color)
{
    std::ifstream in;

    in.open(filename, std::ifstream::in);

    if (in.fail())
        return;

    std::string line;

    while (!in.eof())
    {
        std::getline(in, line);

        std::istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vector3f v;

            for (int i = 0; i < 3; i++)
                iss >> v[i];

            verts.push_back(v);
        }
        else if (!line.compare(0, 3, "vn "))
        {
            iss >> trash >> trash;
            Vector3f n;

            for (int i = 0; i < 3; i++)
                iss >> n[i];

            norms.push_back(n);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<Vector3i> f;
            Vector3i tmp;

            iss >> trash;

            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2])
            {
                for (int i = 0; i < 3; i++)
                    tmp[i]--;

                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }

    //std::cerr << "# v#" << verts.size() << " f# " << faces.size() << std::endl;

    //doScale();
}



// Center
Vector3f& Model::getCenter()
{
    return center;
}

void      Model::setCenter(const Vector3f& newCenter)
{
    center = newCenter;
}



// Vertes
int       Model::getVertsCount()
{
    return verts.size();
}

Vector3f& Model::vert(const int& index)
{
    return verts[index];
}



// Faces
int              Model::getFacesCount()
{
    return faces.size();
}

std::vector<int> Model::face(const int& idx)
{
    std::vector<int> face;
    size_t size = faces[idx].size();

    for (size_t i = 0; i < size; i++)
        face.push_back(faces[idx][i][0]);

    return face;
}



// Normals
int       Model::getNormsCount()
{
    return norms.size();
}

Vector3f& Model::norm(const int& iface, const int& nvert)
{
    int idx = faces[iface][nvert][2];
    return norms[idx].normalize();
}



// Color
QColor& Model::getColor()
{
    return color;
}

void    Model::setColor(const QColor& newColor)
{
    color = newColor;
}











/*
void Model::scale(float k)
{
    int nverts = verts.size();

    for (int i = 0; i < nverts; i++)
    {
        verts[i].x *= k;
        verts[i].y *= k;
        verts[i].z *= k;
    }
}

void Model::doScale()
{
    float k = 1;
    int nverts = verts.size();

    for (int i = 0; i < nverts; i++)
    {
        scale(k);
    }
}
*/

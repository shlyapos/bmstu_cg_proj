#include "model.h"

Model::Model(const char *filename, QColor& color)
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
    std::cerr << "# v#" << verts.size() << " f# " << faces.size() << std::endl;

    this->color = color;
    doScale();
}

Model::~Model()
{

}



int Model::getVertsCount()
{
    return this->verts.size();
}

int Model::getFacesCount()
{
    return this->faces.size();
}

QColor Model::getColor()
{
    return this->color;
}



Vector3f Model::vert(int index)
{
    return this->verts[index];
}

std::vector<int> Model::face(int index)
{
    std::vector<int> face;

    for (int i = 0; i < (int)faces[index].size(); i++)
        face.push_back(faces[index][i][0]);

    return face;
}

Vector3f Model::norm(int iface, int nvert)
{
    int idx = faces[iface][nvert][2];
    return norms[idx].normalize();
}





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
    float k = 0.3;
    int nverts = verts.size();

    for (int i = 0; i < nverts; i++)
    {
        if (verts[i].x > 1 || verts[i].y > 1 || verts[i].z > 1)
        {
            scale(k);
        }
    }
}

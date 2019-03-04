#include "objreader.ih"

vector<float> ObjReader::raw_normals()
{
    vector<float> normals;

    for (Face const &face : d_faces)
    {
        for (Index const &index : face)
        {
            normals.insert(normals.end(),
            {
                d_normals[index.normal - 1].x,
                d_normals[index.normal - 1].y,
                d_normals[index.normal - 1].z
            });
        }
    }

    return normals;
}
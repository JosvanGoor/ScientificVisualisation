#include "objreader.ih"

vector<float> ObjReader::raw_vertices()
{
    vector<float> vertices;

    for (Face const &face : d_faces)
    {
        for (Index const &index : face)
        {
            vertices.insert(vertices.end(),
            {
                d_vertices[index.vertex - 1].x,
                d_vertices[index.vertex - 1].y,
                d_vertices[index.vertex - 1].z
            });
        }
    }

    return vertices;
}
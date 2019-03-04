#include "objreader.ih"

vector<Triangle> ObjReader::extract_triangles()
{
    vector<Triangle> triangles;

    for (size_t idx = 0; idx < d_faces.size(); ++idx)
    {
        Triangle tri;
        tri.p1 = extract_vertex(d_faces[idx][0]);
        tri.p2 = extract_vertex(d_faces[idx][1]);
        tri.p3 = extract_vertex(d_faces[idx][2]);
        triangles.push_back(tri);
    }

    return triangles;
}

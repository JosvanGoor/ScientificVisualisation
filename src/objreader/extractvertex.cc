#include "objreader.ih"

Vertex ObjReader::extract_vertex(Index const &index)
{
    Vertex vertex = {};
    vertex.d_position = d_vertices[index.vertex - 1];

    if (index.texcoord != 0)
        vertex.d_texcoords = d_texcoords[index.texcoord - 1];
    
    if (index.normal != 0)
        vertex.d_normal = d_normals[index.normal - 1];

    return vertex;
}
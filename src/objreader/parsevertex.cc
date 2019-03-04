#include "objreader.ih"



void ObjReader::parse_vertex(string const &line)
{
    stringstream ss(line);
    char type;
    ss >> type;
    
    if (type != 'v')
        throw "illegal parser state"s;

    glm::vec3 vertex;
    ss >> vertex.x;
    ss >> vertex.y;
    ss >> vertex.z;

    d_vertices.push_back(vertex);
    // cout << "V  parsed [" << vertex.x << ", " << vertex.y << ", " << vertex.z << "]\n";
}
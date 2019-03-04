#include "objreader.ih"

void ObjReader::parse_normal(std::string const &line)
{
    stringstream ss(line);
    string type;
    ss >> type;

    if (type != "vn")
        throw "illegal parser state"s;

    glm::vec3 vertex;
    ss >> vertex.x;
    ss >> vertex.y;
    ss >> vertex.z;

    d_normals.push_back(vertex);
    // cout << "VN parsed [" << vertex.x << ", " << vertex.y << ", " << vertex.z << "]\n";
    
}
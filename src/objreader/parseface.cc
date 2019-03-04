#include "objreader.ih"

void ObjReader::parse_face(string const &line)
{
    stringstream ss(line);
    char type;
    ss >> type;

    if (type != 'f')
        throw "illegal parser state"s;

    Face face;
    string index;
    while(!ss.eof())
    {
        ss >> index;
        face.push_back(parse_index(index));
    }

    d_faces.push_back(face);
}
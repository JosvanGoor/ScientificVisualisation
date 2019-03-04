#include "objreader.ih"

ObjReader::ObjReader(string const &file)
{
    ifstream in{file};

    while (!in.eof())
    {
        string buffer;
        getline(in, buffer);

        if (buffer.find("vn") == 0)
            parse_normal(buffer);
        else if (buffer.find("vt") == 0)
            continue;
        else if (buffer.find("v") == 0)
            parse_vertex(buffer);
        else if (buffer.find("f") == 0)
            parse_face(buffer);
    }

    cout << "parsed " << d_vertices.size() << " vertices\n";
    cout << "parsed " << d_normals.size() << " normals\n";
    cout << "parsed " << d_texcoords.size() << " texcoords\n";
    cout << "parsed " << d_faces.size() << " faces\n";
}
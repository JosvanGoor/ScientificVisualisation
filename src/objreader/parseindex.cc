#include "objreader.ih"

Index ObjReader::parse_index(string const &text)
{
    stringstream ss(text);
    vector<string> bits;
    string buffer;

    while(getline(ss, buffer, '/'))
    {
        bits.push_back(buffer);
    }

    Index index = {};
    index.vertex = stoi(bits[0]);
    
    if (bits.size() > 1 && !bits[1].empty())
        index.texcoord = stoi(bits[1]);

    if (bits.size() > 2 && !bits[2].empty())
        index.normal = stoi(bits[2]);

    return index;
}
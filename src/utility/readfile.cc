#include "utility.ih"

string read_file(string const &file)
{
    ifstream in {file, std::ios::binary};

    if(!in.is_open())
        throw "Failed to read file."s;

    size_t length;
    in.seekg(0, ios::end);
    length = in.tellg();
    in.seekg(0, ios::beg);

    char *buffer = new char[length + 1];
    in.read(buffer, length);
    buffer[length] = '\0';

    string rval{buffer};
    delete[] buffer;

    return rval;
}
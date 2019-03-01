#include "string.ih"

#include <iostream>

RenderFont::String::~String()
{
    if (d_vao)
        glDeleteVertexArrays(1, &d_vao);
    if (d_buffer)
        glDeleteBuffers(1, &d_buffer);
}
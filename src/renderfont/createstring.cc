#include "renderfont.ih"

RenderFont::String RenderFont::create_string(string const &text, GLuint storage)
{
    String rval(storage, d_size);
    rval.buffer_string(text, d_characters);
    return move(rval);
}
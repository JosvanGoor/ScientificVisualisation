#include "renderfont.ih"

RenderFont::~RenderFont()
{
    glDeleteTextures(1, &d_charmap);
    glDeleteProgram(d_program);
}
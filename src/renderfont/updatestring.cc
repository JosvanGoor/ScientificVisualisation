#include "renderfont.ih"

void RenderFont::update_string(String &str, string const &text)
{
    str.buffer_string(text, d_characters);
}

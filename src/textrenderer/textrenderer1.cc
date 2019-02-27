#include "textrenderer.ih"

TextRenderer::TextRenderer(string const &font, size_t size)
{
    load_glyphs(font, size);
}
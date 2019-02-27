#include "textrenderer.ih"

TextRenderer::TextRenderer(string const &font, size_t size)
{
    load_program();
    load_buffers();
    load_glyphs(font, size);
}
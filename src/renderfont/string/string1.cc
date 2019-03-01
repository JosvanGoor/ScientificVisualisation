#include "string.ih"

RenderFont::String::String(GLuint store_mode, size_t height)
:   d_vao(0),
    d_buffer(0),
    d_storage_mode(store_mode),
    d_color(1.0f, 1.0f, 1.0f),
    d_outline_color(0.0f, 0.0f, 0.0f),
    d_drawcount(0),
    d_width(0),
    d_height(height)
{
    generate_buffers();
}
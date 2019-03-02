#include "string.ih"

RenderFont::String::String(String &&move)
:   d_vao(move.d_vao),
    d_buffer(move.d_buffer),
    d_storage_mode(move.d_storage_mode),
    d_color(move.d_color),
    d_outline_color(move.d_outline_color),
    d_drawcount(move.d_drawcount),
    d_width(move.d_width),
    d_height(move.d_height),
    d_text(move.d_text)
{
    move.d_vao = 0;
    move.d_buffer = 0;
    move.d_text = "";
}
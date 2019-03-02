#include "renderfont.ih"

RenderFont::RenderFont(RenderFont &&other)
:   d_program(other.d_program),
    d_projection(move(other.d_projection)),
    d_transform_loc(other.d_transform_loc),
    d_position_loc(other.d_position_loc),
    d_color_loc(other.d_color_loc),
    d_size(other.d_size),
    d_charmap(other.d_charmap),
    d_characters(move(other.d_characters))
{
    other.d_program = 0;
    other.d_charmap = 0;
}
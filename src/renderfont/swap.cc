#include "renderfont.ih"

void RenderFont::swap(RenderFont &other)
{
    std::swap(d_program, other.d_program);
    std::swap(d_size, other.d_size);
    std::swap(d_charmap, other.d_charmap);
    std::swap(d_transform_loc, other.d_transform_loc);
    std::swap(d_position_loc, other.d_position_loc);
    std::swap(d_color_loc, other.d_color_loc);
    d_characters.swap(other.d_characters);

    glm::mat4 temp = d_projection;
    d_projection = other.d_projection;
    other.d_projection = temp;
}
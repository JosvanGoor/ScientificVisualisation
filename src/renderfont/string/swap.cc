#include "string.ih"

void RenderFont::String::swap(String &other)
{
    std::swap(d_vao, other.d_vao);
    std::swap(d_buffer, other.d_buffer);
    std::swap(d_storage_mode, other.d_storage_mode);
    std::swap(d_drawcount, other.d_drawcount);
    std::swap(d_width, other.d_width);
    std::swap(d_height, other.d_height);
    d_text.swap(other.d_text);

    glm::vec3 temp = other.d_color;
    other.d_color = d_color;
    d_color = temp;
    
    temp = other.d_outline_color;
    other.d_outline_color = d_outline_color;
    d_outline_color = temp;
}
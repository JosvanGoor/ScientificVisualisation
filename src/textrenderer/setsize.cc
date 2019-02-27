#include "textrenderer.ih"

void TextRenderer::set_size(size_t width, size_t height)
{
    d_width = width;
    d_height = height;

    d_projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}
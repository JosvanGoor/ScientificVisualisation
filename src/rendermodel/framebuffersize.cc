#include "rendermodel.ih"

void RenderModel::framebuffer_size(size_t width, size_t height)
{
    d_projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}
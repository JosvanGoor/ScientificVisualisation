#include "arrow3drendermodel.ih"

void Arrow3dRenderModel::set_framebuffer_size(size_t width, size_t height)
{
    d_width = width;
    d_height = d_height;

    d_projection = glm::perspective
    (
        glm::radians(45.0f),                    // fov
        static_cast<float>(width) / height,     // aspect ratio
        0.1f,                                   // near plane
        1000.0f                                  // far plane
    );
}
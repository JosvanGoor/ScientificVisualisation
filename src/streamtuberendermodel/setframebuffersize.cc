#include "streamtuberendermodel.ih"

void StreamtubeRenderModel::set_framebuffer_size(size_t width, size_t height)
{
    d_projection = glm::perspective
    (
        glm::radians(45.0f),                    // fov
        static_cast<float>(width) / height,     // aspect ratio
        0.1f,                                   // near plane
        1000.0f                                  // far plane
    );
}
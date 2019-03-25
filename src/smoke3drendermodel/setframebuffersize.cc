#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_framebuffer_size(size_t width, size_t height, size_t gridsize)
{
    d_width = width;
    d_height = height;
    d_gridsize = gridsize;

    d_projection = glm::perspective
    (
        glm::radians(45.0f),                    // fov
        static_cast<float>(width) / height,     // aspect ratio
        0.1f,                                   // near plane
        500.0f                                  // far plane
    );
    
    d_lookat = glm::lookAt
    (
        vec3(0.0f, -20.0f, 15.0f), // cam pos
        vec3(0.0f, 0.0f, 0.0f), // center / looking at
        vec3(0.0f, 0.0f, 1.0f) // up
    );

    update_smoke_mapping(gridsize);
    generate_framebuffer();
}
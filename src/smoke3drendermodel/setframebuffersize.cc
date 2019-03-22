#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_framebuffer_size(size_t width, size_t height, size_t gridsize)
{
    d_width = width;
    d_height = height;
    d_gridsize = gridsize;

    d_projection = ortho
    (
        0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height),
        -10.0f, 10.0f
    );
    
    update_smoke_mapping(gridsize);
    generate_framebuffer();
}
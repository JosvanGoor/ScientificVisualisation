#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_framebuffer_size(size_t width, size_t height, size_t gridsize)
{
    d_width = width;
    d_height = height;

    d_projection = ortho
    (
        0.0f, static_cast<float>(width),
        0.0f, static_cast<float>(height),
        -1.0f, 1.0f
    );
    d_bar_projection = d_projection;

    update_smoke_mapping(gridsize);
}
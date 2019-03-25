#include "smoke3drendermodel.ih"

Smoke3dRenderModel::Smoke3dRenderModel()
:   d_program(0),
    d_smoke_attributes(0),
    d_smoke_vertices(0),
    d_smoke_normals(0),
    d_smoke_texcoords(0),
    d_framebuffer(0),
    d_color_tex(0),
    d_depth_rbuf(0),
    d_hmin(0.0f),
    d_hmax(0.0f),
    d_width(100),
    d_height(100),
    d_gridsize(100),
    d_drawcount(0),
    d_lookat(1.0f),
    d_projection(1.0f),
    d_sampler_loc(0),
    d_projection_loc(0)
{

    d_lookat = glm::lookAt
    (
        vec3(0.0f, -20.0f, 15.0f), // cam pos
        vec3(0.0f, 0.0f, 0.0f), // center / looking at
        vec3(0.0f, 0.0f, 1.0f) // up
    );

}
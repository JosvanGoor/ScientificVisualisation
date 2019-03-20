#include "smoke3drendermodel.ih"

Smoke3dRenderModel::Smoke3dRenderModel()
:   d_program(0),
    d_smoke_attributes(0),
    d_smoke_vertices(0),
    d_smoke_normals(0),
    d_smoke_colors(0),
    d_bar_attributes(0),
    d_bar_vertex(0),
    d_bar_projection(1.0f),
    d_cmin(0.0f),
    d_cmax(0.0f),
    d_hmin(0.0f),
    d_hmax(0.0f),
    d_width(100),
    d_height(100),
    d_drawcount(0),
    d_colormapping(0),
    d_projection(1.0f),
    d_projection_loc(0),
    d_colormapping_loc(0),
    d_limit_loc(0)
{ }
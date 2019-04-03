#include "isoline2drendermodel.ih"

Isoline2dRenderModel::Isoline2dRenderModel()
:   d_program(0),
    d_attribute_object(0),
    d_vertex_buffer(0),
    d_colormapping(ColorMapping::BLACK),
    d_color_location(0),
    d_projection_location(0)
{ }

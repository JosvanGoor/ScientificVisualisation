#include "glyph2drendermodel.ih"
#include<iostream>

Glyph2dRenderModel::Glyph2dRenderModel()
:   d_glyph_dim(50),
    d_projection(glm::ortho(0.0f, 250.0f, 0.0f, 250.0f, -1.0f, 1.0f)),
    d_program(0),
    d_attribute_object(0),
    d_vertex_buffer(0),
    d_position_buffer(0),
    d_rotation_buffer(0),
    d_color_buffer(0)
{   
}
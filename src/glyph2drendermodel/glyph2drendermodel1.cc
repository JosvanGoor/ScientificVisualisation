#include "glyph2drendermodel.ih"
#include<iostream>

Glyph2dRenderModel::Glyph2dRenderModel()
:   d_glyph_dim(50),
    d_projection(-1.0f),
    d_program(0),
    d_attribute_object(0),
    d_vertex_buffer(0),
    d_position_buffer(0),
    d_rotation_buffer(0),
    d_color_buffer(0)
{   
    d_lookat = glm::lookAt
    (
        glm::vec3(0.0f, -20.0f, 15.0f), // cam pos
        glm::vec3(0.0f, 0.0f, 0.0f), // center / looking at
        glm::vec3(0.0f, 0.0f, 1.0f) // up
    );
}
#include "linerendermodel.ih"

#include <iostream>

LineRenderModel::LineRenderModel()
:   RenderModel()
{
    load_shaders("shaders/line_vertex.glsl", "shaders/line_fragment.glsl");
    prepare_buffers(2, 2);
}
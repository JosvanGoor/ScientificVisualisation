#include "smokerendermodel.ih"

SmokeRenderModel::SmokeRenderModel()
:   RenderModel()
{
    load_shaders("shaders/smoke_vertex.glsl", "shaders/smoke_fragment.glsl");
    prepare_buffers(2, 1);
}
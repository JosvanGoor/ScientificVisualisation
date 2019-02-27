#include "smokerendermodel.ih"

SmokeRenderModel::SmokeRenderModel()
:   RenderModel(),
    d_textrender("fonts/comic.ttf", 16)
{
    load_shaders("shaders/smoke_vertex.glsl", "shaders/smoke_fragment.glsl");
    prepare_buffers(2, 1);
    build_bar();
}
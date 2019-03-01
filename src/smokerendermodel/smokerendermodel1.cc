#include "smokerendermodel.ih"

SmokeRenderModel::SmokeRenderModel()
:   RenderModel(),
    d_renderfont("fonts/comic.ttf", 16),
    d_maxtext(d_renderfont.create_string("1.0e0", GL_STREAM_DRAW)),
    d_mintext(d_renderfont.create_string("0.0e0", GL_STREAM_DRAW))
{
    load_shaders("shaders/smoke_vertex.glsl", "shaders/smoke_fragment.glsl");
    prepare_buffers(2, 1);
    build_bar();
}
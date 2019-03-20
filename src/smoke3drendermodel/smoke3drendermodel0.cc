#include "smoke3drendermodel.ih"

Smoke3dRenderModel::~Smoke3dRenderModel()
{
    glDeleteProgram(d_program);
    glDeleteVertexArrays(1, &d_smoke_attributes);
    glDeleteBuffers(1, &d_smoke_vertices);
    glDeleteBuffers(1, &d_smoke_height);
    glDeleteBuffers(1, &d_smoke_colors);
    glDeleteVertexArrays(1, &d_bar_attributes);
    glDeleteBuffers(1, &d_bar_vertex);
}
#include "smoke3drendermodel.ih"

Smoke3dRenderModel::~Smoke3dRenderModel()
{
    glDeleteProgram(d_program);
    glDeleteVertexArrays(1, &d_smoke_attributes);
    glDeleteBuffers(1, &d_smoke_vertices);
    glDeleteBuffers(1, &d_smoke_normals);
    
    glDeleteFramebuffers(1, &d_framebuffer);
    glDeleteTextures(1, &d_color_tex);
    glDeleteRenderbuffers(1, &d_depth_rbuf);

}
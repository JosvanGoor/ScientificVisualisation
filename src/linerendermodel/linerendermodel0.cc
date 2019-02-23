#include "linerendermodel.ih"

LineRenderModel::~LineRenderModel()
{
    glUseProgram(0);
    
    glDeleteProgram(d_program);
    glDeleteVertexArrays(1, &d_attribute_object);
    glDeleteBuffers(1, &d_vertex_buffer);
    glDeleteBuffers(1, &d_color_buffer);
}
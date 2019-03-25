#include "arrow3drendermodel.ih"

void Arrow3dRenderModel::render()
{
    size_t numarrows = d_arrow_dim * d_arrow_dim;

    glEnable(GL_DEPTH_TEST);
    // glClear(GL_DEPTH_BUFFER_BIT); //??

    glm::mat4 mvp = d_projection * d_lookat;

    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArraysInstanced(GL_TRIANGLES, 0, d_drawcount, numarrows);

    glDisable(GL_DEPTH_TEST);
}
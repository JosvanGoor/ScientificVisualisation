#include "arrow3drendermodel.ih"

void Arrow3dRenderModel::render_2d()
{
    size_t numarrows = d_arrow_dim * d_arrow_dim;

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT); //??

    glm::mat4 lookat = glm::lookAt
    (
        glm::vec3(0.01f, 0.0f, 10.25f), // yes
        glm::vec3(0.0f, 0.0f, 0.0f), // trust me
        glm::vec3(0.0f, 1.0f, 0.0f) // it works
    );

    glm::mat4 projection = glm::perspective(radians(90.0f), 3.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * lookat;

    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArraysInstanced(GL_TRIANGLES, 0, d_drawcount, numarrows);

    glDisable(GL_DEPTH_TEST);
}
#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::render_2d()
{
    /* Calculate positions */
    size_t numglyphs = d_glyph_dim * d_glyph_dim;

    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 lookat = glm::lookAt
    (
        glm::vec3(0.0f, 0.0f, 10.1f), // yes
        glm::vec3(0.0f, 0.0f, 0.0f), // trust me
        glm::vec3(0.0f, 1.0f, 0.0f) // it works
    );

    glm::mat4 projection = glm::perspective(radians(90.0f), 3.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 mvp = projection * lookat;

    // do rendering
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, numglyphs);

    // glDisable(GL_DEPTH_TEST);
}
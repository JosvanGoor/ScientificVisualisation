#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::render()
{
    /* Calculate positions */
    size_t numglyphs = d_glyph_dim * d_glyph_dim;

    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     glm::mat4 mvp = d_projection * d_lookat;

    // do rendering
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, numglyphs);

    // glDisable(GL_DEPTH_TEST);
}
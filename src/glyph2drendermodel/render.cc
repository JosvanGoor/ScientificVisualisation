#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::render()
{
    /* Calculate positions */
    size_t numglyphs = d_glyph_dim * d_glyph_dim;

    // do rendering
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, numglyphs);
}
#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::render()
{
    /* Calculate positions */
    size_t numglyphs = d_glyph_dim * d_glyph_dim;

    vector<float> positions;
    positions.reserve(2 * numglyphs);

    for (size_t row = 0; row < d_glyph_dim; ++row)
    {
        for (size_t col = 0; col < d_glyph_dim; ++col)
        {
            // xpos
            positions.push_back(d_coord_start + (col * d_coord_advance));
            // ypos
            positions.push_back(d_coord_start + (row * d_coord_advance));
        }
    }

    //update position buffer
    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(positions), positions.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // do rendering
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, numglyphs);
}
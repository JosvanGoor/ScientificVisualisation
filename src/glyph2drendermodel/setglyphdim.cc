#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::set_glyph_dim(size_t dim)
{
    d_glyph_dim = dim;

    float d_coord_advance = 
        20.0f / static_cast<float>(d_glyph_dim);
    float d_coord_start = -10.0f + d_coord_advance / 2.0f;

    /* Upload glyph positions once */
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
            // zpos
            positions.push_back(0.1f);
        }
    }

    //update position buffer
    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(positions), positions.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include "arrow3drendermodel.ih"

void Arrow3dRenderModel::set_arrow_dim(size_t dim)
{
    d_arrow_dim = dim;

    float d_coord_advance = 82.0f / static_cast<float>(dim);
    float d_coord_start = -41.0f + (d_coord_advance / 2.0f);

    size_t numarrows = dim * dim;
    vector<float> positions;
    positions.reserve(2 * numarrows);

    for (size_t row = 0; row < d_arrow_dim; ++row)
    {
        for (size_t col = 0; col < d_arrow_dim; ++col)
        {
            // xpos
            positions.push_back(d_coord_start + (col * d_coord_advance));
            // ypos
            positions.push_back(d_coord_start + (row * d_coord_advance));
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(positions), positions.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
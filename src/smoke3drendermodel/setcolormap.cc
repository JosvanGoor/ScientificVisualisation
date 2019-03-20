#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_colormap(vector<float> const &color, float min, float max)
{
    vector<float> remap;

    for (size_t row = 0; row < (d_gridsize - 1); ++row)
    {
        for (size_t col = 0; col < (d_gridsize - 1); ++col)
        {
            // Define quad as 2 triangles, quad vertices are
            // 2 *--* 3
            //   |  |
            // 1 *--* 4
            // then the first tri is 1, 2, 4
            // and the second tri is 4, 2, 3
            // So we need to add 3 color values for every triangle
            // we'll work per quad.

            remap.insert(remap.end(),
            {
                // tri 1
                color[row * d_gridsize + col],
                color[(row + 1) * d_gridsize + col],
                color[row * d_gridsize + (col + 1)],

                // tri 2
                color[row * d_gridsize + (col + 1)],
                color[(row + 1) * d_gridsize + col],
                color[(row + 1) * d_gridsize + (col + 1)],
            });
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_colors);
    glBufferData(GL_ARRAY_BUFFER, remap.size() * sizeof(float), remap.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_cmin = min;
    d_cmax = max;
}
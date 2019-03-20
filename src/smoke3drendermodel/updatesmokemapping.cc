#include "smoke3drendermodel.ih"

vector<float> Smoke3dRenderModel::update_smoke_mapping(size_t gridsize, vector<float> const &heights)
{
    float wn = d_width / static_cast<double>(gridsize + 1);
    float hn = d_height / static_cast<double>(gridsize + 1);

    vector<float> triangles;
    for (size_t row = 0; row < (gridsize - 1); ++row)
    {
        float ypos = hn + (row * hn);
        for (size_t col = 0; col < (gridsize - 1); ++col)
        {
            float xpos = wn + (col * wn);
            // Define quad as 2 triangles, quad vertices are
            // 2 *--* 3
            //   |  |
            // 1 *--* 4
            // then the first tri is 1, 2, 4
            // and the second tri is 4, 2, 3
            triangles.insert(triangles.end(),
            {
                // tri 1
                xpos,       ypos,       0.0f,
                xpos,       ypos + hn,  0.0f,
                xpos + wn,  ypos,       0.0f,

                // tri 2
                xpos + wn,  ypos,       0.0f,
                xpos,       ypos + hn,  0.0f,
                xpos + wn,  ypos + hn,  0.0f
            });
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangles.size(), triangles.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    d_drawcount = triangles.size() / 3;

    return triangles;
}
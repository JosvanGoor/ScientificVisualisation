#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::update_smoke_mapping(size_t gridsize)
{
    float wn = d_width / static_cast<double>(gridsize + 1);
    float hn = d_height / static_cast<double>(gridsize + 1);
    float ti = 1.0f / static_cast<float>(gridsize);

    d_triangles.clear();
    vector<float> texcoords;
    for (size_t row = 0; row < (gridsize - 1); ++row)
    {
        float ypos = hn + (row * hn);
        float typos = row * ti;
        for (size_t col = 0; col < (gridsize - 1); ++col)
        {
            float xpos = wn + (col * wn);
            float txpos = col * ti;
            // Define quad as 2 triangles, quad vertices are
            // 2 *--* 3
            //   |  |
            // 1 *--* 4
            // then the first tri is 1, 2, 4
            // and the second tri is 4, 2, 3
            d_triangles.insert(d_triangles.end(),
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

            texcoords.insert(texcoords.end(),
            {
                txpos,      typos,
                txpos,      typos + ti,
                txpos + ti, typos,

                txpos + ti, typos,
                txpos,      typos + ti,
                txpos + ti, typos + ti
            });
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_triangles.size(), d_triangles.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_texcoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texcoords.size(), texcoords.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_drawcount = d_triangles.size() / 3;
}
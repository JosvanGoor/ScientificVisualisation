#include "smoke3drendermodel.ih"

vector<float> Smoke3dRenderModel::update_smoke_mapping(size_t gridsize)
{
    double wn = d_width / static_cast<double>(gridsize + 1);
    double hn = d_height / static_cast<double>(gridsize + 1);

    vector<float> triangles;

    for (int jdx = 0; jdx < (gridsize - 1); ++jdx)
    {
        int idx = 0;
        float px = wn + idx * wn; // think about this...
        float py = hn + jdx * hn;

        triangles.push_back(px);
        triangles.push_back(py);
        triangles.push_back(0.0f);

        for (; idx < (gridsize - 1); ++idx)
        {
            px = wn + idx * wn;
            py = hn + (jdx + 1) * hn;
            triangles.push_back(px);
            triangles.push_back(py);
            triangles.push_back(0.0f);

            px = wn + (idx + 1) * wn;
            py = hn + jdx * hn;
            triangles.push_back(px);
            triangles.push_back(py);
            triangles.push_back(0.0f);
        }

        px = wn + (gridsize - 1) * wn;
        py = hn + (jdx + 1) * hn;
        triangles.push_back(px);
        triangles.push_back(py);
        triangles.push_back(0.0f);
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * triangles.size(), triangles.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    d_drawcount = gridsize;

    return triangles;
}
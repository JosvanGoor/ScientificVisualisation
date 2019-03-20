#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_heightmap(vector<float> const &height, float min, float max)
{
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_height);
    glBufferData(GL_ARRAY_BUFFER, height.size() * sizeof(float), height.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_hmin = min;
    d_hmax = max;
}
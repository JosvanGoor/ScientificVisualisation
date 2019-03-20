#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::set_colormap(vector<float> const &color, float min, float max)
{
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_colors);
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(float), color.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_cmin = min;
    d_cmax = max;
}
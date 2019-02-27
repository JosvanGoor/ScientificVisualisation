#include "rendermodel.ih"

void RenderModel::set_color_data(vector<float> const &colors, float v_min, float v_max)
{
    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    d_min = v_min;
    d_max = v_max;
}
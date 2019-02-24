#include "smokerendermodel.ih"

#include <iostream>

void SmokeRenderModel::set_data(vector<float> const &tristrip, vector<float> const &colors)
{
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, tristrip.size() * sizeof(float), tristrip.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_drawcount = (tristrip.size() / 2) / (d_rows - 1);
    cout << d_drawcount << "\n";
}
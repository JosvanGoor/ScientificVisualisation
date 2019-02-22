#include "linerendermodel.ih"

void LineRenderModel::set_data(vector<float> const &lines, vector<float> const &colors)
{

    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, lines.size() * sizeof(float), lines.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STREAM_DRAW);

    d_linecount = lines.size() / 4;
}
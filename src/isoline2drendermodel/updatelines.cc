#include "isoline2drendermodel.ih"
#include <iostream>

void Isoline2dRenderModel::update_lines(vector<float> const &lines)
{
    //cout << "Drawing lines: " << lines.size() << '\n';
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lines.size(), lines.data(), GL_STREAM_DRAW);
    d_drawcount = lines.size() / 2;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
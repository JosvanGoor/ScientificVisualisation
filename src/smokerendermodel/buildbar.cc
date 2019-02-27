#include "smokerendermodel.ih"

void SmokeRenderModel::build_bar()
{
    glGenVertexArrays(1, &d_bar_vao);
    glBindVertexArray(d_bar_vao);

    glGenBuffers(1, &d_bar_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, d_bar_vertices);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_bar_colors);
    glBindBuffer(GL_ARRAY_BUFFER, d_bar_colors);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
#include "textrenderer.ih"

void TextRenderer::load_buffers()
{
    glGenVertexArrays(1, &d_attributes);
    glBindVertexArray(d_attributes);

    glGenBuffers(1, &d_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
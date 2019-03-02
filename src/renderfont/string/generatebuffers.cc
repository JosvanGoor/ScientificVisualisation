#include "string.ih"

void RenderFont::String::generate_buffers()
{
    glGenVertexArrays(1, &d_vao);
    glBindVertexArray(d_vao);

    glGenBuffers(1, &d_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, d_storage_mode);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
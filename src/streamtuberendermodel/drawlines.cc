#include "streamtuberendermodel.ih"

void StreamtubeRenderModel::draw_lines(vector<float> const &lines, size_t layers)
{
    vector<float> vertices;

    for (size_t idx = 0; idx < ((lines.size() / 3) - 1); ++idx)
    {
        // start
        vertices.push_back((lines[idx * 3 + 0] - 0.5f) * 20.0f);
        vertices.push_back((lines[idx * 3 + 1] - 0.5f) * 20.0f);
        vertices.push_back(lines[idx * 3 + 2] * 10.0f);

        // end
        vertices.push_back((lines[idx * 3 + 3] - 0.5f) * 20.0f);
        vertices.push_back((lines[idx * 3 + 4] - 0.5f) * 20.0f);
        vertices.push_back(lines[idx * 3 + 5] * 10.0f);
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(d_program);
    glBindVertexArray(d_attribute_buffer);
    
    glm::mat4 mvp = d_projection * d_lookat;
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));

    glDrawArrays(GL_LINES, 0, vertices.size() / 3);
}
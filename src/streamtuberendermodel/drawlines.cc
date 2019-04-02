#include "streamtuberendermodel.ih"

void StreamtubeRenderModel::draw_lines(vector<float> const &lines, size_t layers)
{
    generate_tubes(lines, layers);
    
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_buffer);

    // glEnable(GL_DEPTH_TEST);

    glm::mat4 mvp = d_projection * d_lookat;
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, d_drawcount);
}
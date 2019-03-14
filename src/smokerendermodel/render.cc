#include "smokerendermodel.ih"

void SmokeRenderModel::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glUniform1i(d_colormapping_location, d_colormapping);
    glUniform2f(d_limit_location, d_min, d_max);

    for (size_t idx = 0; idx < (d_drawcount - 1); ++idx)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, idx * d_drawcount * 2, d_drawcount * 2);
    }
}
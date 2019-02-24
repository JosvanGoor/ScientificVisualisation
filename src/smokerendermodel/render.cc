#include "smokerendermodel.ih"

void SmokeRenderModel::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    
    for (size_t idx = 0; idx < (d_rows - 1); ++idx)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, idx * d_drawcount, d_drawcount);
    }

}
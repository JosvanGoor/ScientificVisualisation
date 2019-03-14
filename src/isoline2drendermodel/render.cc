#include "isoline2drendermodel.ih"

void Isoline2dRenderModel::render()
{
    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);

    glLineWidth(3.0f); //sets line width

    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glUniform3f(d_color_location, d_color.x, d_color.y, d_color.z);

    glDrawArrays(GL_LINES, 0, d_drawcount);
}
#include "linerendermodel.ih"

#include <iostream>

void LineRenderModel::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // glPolygonMode(GL_POLYGON_MODE, GL_LINES);

    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glDrawArrays(GL_LINES, 0, 2 * d_linecount);
}
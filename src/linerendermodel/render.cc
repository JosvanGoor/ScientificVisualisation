#include "linerendermodel.ih"

void LineRenderModel::render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(d_program);
    glBindVertexArray(d_attribute_object);
    glDrawArrays(GL_LINES, 0, 2 * d_linecount);
}
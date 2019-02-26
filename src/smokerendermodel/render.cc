#include "smokerendermodel.ih"
#include <iostream>

void SmokeRenderModel::render()
{
    cout << "1\n";
    glClear(GL_COLOR_BUFFER_BIT);
    cout << "2\n";

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    cout << "3\n";
    glUseProgram(d_program);
    cout << "4\n";
    glBindVertexArray(d_attribute_object);
    cout << "5\n";
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    cout << "6\n";
    glUniform1i(d_colormapping_location, d_colormapping);
    cout << "7\n";

    for (size_t idx = 0; idx < (d_drawcount - 1); ++idx)
    {
        glDrawArrays(GL_TRIANGLE_STRIP, idx * d_drawcount * 2, d_drawcount * 2);
    }

}
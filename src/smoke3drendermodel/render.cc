#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(d_program);
    glBindVertexArray(d_smoke_attributes);
    glUniformMatrix4fv(d_projection_loc, 1, GL_FALSE, value_ptr(d_projection));
    glUniform1i(d_colormapping_loc, d_colormapping);
    glUniform2f(d_limit_loc, d_cmin, d_cmax);

    for (size_t idx = 0; idx < (d_drawcount - 1); ++idx)
        glDrawArrays(GL_TRIANGLE_STRIP, idx * d_drawcount * 2, d_drawcount * 2);

    glDisable(GL_DEPTH_TEST);
}
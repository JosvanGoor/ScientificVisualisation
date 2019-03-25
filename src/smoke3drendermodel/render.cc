#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mvp = d_projection * d_lookat;

    // mvp = ortho
    // (
    //     0.0f, static_cast<float>(d_width), 0.0f, static_cast<float>(d_height), -1.0f, 1.0f
    // );

    glUseProgram(d_program);
    glBindVertexArray(d_smoke_attributes);
    glUniformMatrix4fv(d_projection_loc, 1, GL_FALSE, value_ptr(mvp));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, d_color_tex);

    glDrawArrays(GL_TRIANGLES, 0, d_drawcount);
    glDisable(GL_DEPTH_TEST);
}
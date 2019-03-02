#include "renderfont.ih"

void RenderFont::render_string(String const &str, glm::vec2 const &pos)
{
    glUseProgram(d_program);
    glBindVertexArray(str.d_vao);

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniformMatrix4fv(d_transform_loc, 1, GL_FALSE, glm::value_ptr(d_projection));
    glUniform2f(d_position_loc, pos.x, pos.y);
    glUniform3f(d_color_loc, str.d_color.x, str.d_color.y, str.d_color.y);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, d_charmap);

    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);

    //cleanup
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}
#include "renderfont.ih"

void RenderFont::render_string_outlined(String const &str, glm::vec2 const &pos)
{
    glUseProgram(d_program);
    glBindVertexArray(str.d_vao);

    glEnable(GL_BLEND);
    // glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUniformMatrix4fv(d_transform_loc, 1, GL_FALSE, glm::value_ptr(d_projection));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, d_charmap);

    glUniform3f(d_color_loc, str.d_outline_color.x, str.d_outline_color.y, str.d_outline_color.y);
    glUniform2f(d_position_loc, pos.x - 2, pos.y);
    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);
    glUniform2f(d_position_loc, pos.x + 2, pos.y);
    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);
    glUniform2f(d_position_loc, pos.x, pos.y - 2);
    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);
    glUniform2f(d_position_loc, pos.x, pos.y + 2);
    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);

    glUniform3f(d_color_loc, str.d_color.x, str.d_color.y, str.d_color.y);
    glUniform2f(d_position_loc, pos.x, pos.y);
    glDrawArrays(GL_TRIANGLES, 0, str.d_drawcount);

    //cleanup
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    // glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
}
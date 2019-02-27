#include "textrenderer.ih"

void TextRenderer::render_string(std::string const &text, float xpos, float ypos, glm::vec3 color)
{
    glUseProgram(d_program);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glUniform3f(d_color_location, color.x, color.y, color.z);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(d_attributes);

    for (char ch : text)
    {
        Character glyph = d_characters[ch];

        float xp = xpos + glyph.bearing.x;
        float yp = ypos - (glyph.size.y - glyph.bearing.y);
        float w = glyph.size.x;
        float h = glyph.size.y;

        float vertices[6][4] = 
        {
            xp,     yp + h,     0.0, 0.0,
            xp,     yp,         0.0, 1.0,
            xp + w, yp,         1.0, 1.0,
            xp,     yp + h,     0.0, 0.0,
            xp + w, yp,         1.0, 1.0,
            xp + w, yp + h,     1.0, 0.0
        };

        glBindTexture(GL_TEXTURE_2D, glyph.texture_id);
        glBindBuffer(GL_ARRAY_BUFFER, d_buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        xpos += (glyph.advance >> 6);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

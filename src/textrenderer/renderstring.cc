#include "textrenderer.ih"

void TextRenderer::render_string(std::string const &text, float xpos, float ypos, glm::vec3 color)
{
    glUseProgram(d_program);

    glUniform3f(glGetUniformLocation(d_program, "text_color"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    
        
}

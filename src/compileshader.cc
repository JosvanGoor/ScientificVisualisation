#include "main.ih"

GLuint compile_shader(string const &source, GLuint type)
{
    GLuint shader = glCreateShader(type);

    char const *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        throw string(log);
    }

    return shader;
}
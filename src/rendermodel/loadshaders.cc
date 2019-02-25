#include "rendermodel.ih"

void RenderModel::load_shaders(string const &vsfile, string const &fsfile)
{
    GLuint vshader = compile_shader(read_file(vsfile), GL_VERTEX_SHADER);
    GLuint fshader = compile_shader(read_file(fsfile), GL_FRAGMENT_SHADER);
    d_program = link_program(vshader, fshader);

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    d_projection_location = glGetUniformLocation(d_program, "u_transform");
}
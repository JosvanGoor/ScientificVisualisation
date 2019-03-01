#include "utility.ih"

GLuint build_program(string const &vfile, string const &ffile)
{
    string vtext = read_file(vfile);
    string ftext = read_file(ffile);

    GLuint vshader = compile_shader(vtext, GL_VERTEX_SHADER);
    GLuint fshader = compile_shader(ftext, GL_FRAGMENT_SHADER);
    GLuint program = link_program(vshader, fshader);
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    return program;
}
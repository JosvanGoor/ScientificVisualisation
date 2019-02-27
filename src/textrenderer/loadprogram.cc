#include "textrenderer.ih"

void TextRenderer::load_program()
{
    string vsource = read_file("shaders/text_vertex.glsl");
    string fsource = read_file("shaders/text_fragment.glsl");
    GLuint vshader = RenderModel::compile_shader(vsource, GL_VERTEX_SHADER);
    GLuint fshader = RenderModel::compile_shader(fsource, GL_FRAGMENT_SHADER);
    d_program = RenderModel::link_program(vshader, fshader);
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    d_projection_location = glGetUniformLocation(d_program, "projection");
    d_color_location = glGetUniformLocation(d_program, "text_color");
    d_sampler_location = glGetUniformLocation(d_program, "text");
}
#include "linerendermodel.ih"

#include <iostream>

LineRenderModel::LineRenderModel()
{
    string vtext = read_file("shaders/line_vertex.glsl");
    string ftext = read_file("shaders/line_fragment.glsl");

    cout << vtext << "\n";
    cout << ftext << "\n";

    GLuint vshader = compile_shader(vtext, GL_VERTEX_SHADER);
    GLuint fshader = compile_shader(ftext, GL_FRAGMENT_SHADER);
    d_program = link_program(vshader, fshader);
    // glDeleteShader(vshader);
    // glDeleteShader(fshader);

    d_linecount = 2;
    d_lines = default_lines();
    d_colors = default_colors();

    cout << "lines size: " << d_lines.size() << "\n";

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, d_lines.size() * sizeof(float), d_lines.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, d_colors.size() * sizeof(float), d_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
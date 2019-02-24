#include "smokerendermodel.ih"

SmokeRenderModel::SmokeRenderModel(size_t rows)
{
    GLuint vshader = compile_shader(read_file("shaders/line_vertex.glsl"), GL_VERTEX_SHADER);
    GLuint fshader = compile_shader(read_file("shaders/line_fragment.glsl"), GL_FRAGMENT_SHADER);
    d_program = link_program(vshader, fshader);
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    d_rows = rows;
    d_drawcount = 8;
    vector<float> tristrip = default_tristrip();
    vector<float> colors = default_colors();

    d_projection = glm::ortho(0.0f, 500.0f, 0.0f, 500.0f, -1.0f, 1.0f);
    d_projection_location = glGetUniformLocation(d_program, "u_transform");

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, tristrip.size() * sizeof(float), tristrip.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
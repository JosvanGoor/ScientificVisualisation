#include "isoline2drendermodel.ih"

void Isoline2dRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/iso2d_vs.glsl",
        "shaders/iso2d_fs.glsl"
    );

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glUseProgram(d_program);
    d_color_location = glGetUniformLocation(d_program, "color");
    d_projection_location = glGetUniformLocation(d_program, "projection");
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    d_drawcount = 0;
    set_size(1, 1); // dummy value
    set_color(glm::vec3(0.0f, 0.0f, 0.0f));
}
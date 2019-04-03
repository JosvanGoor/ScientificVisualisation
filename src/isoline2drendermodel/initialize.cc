#include "isoline2drendermodel.ih"

void Isoline2dRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/smoke_vertex.glsl",
        "shaders/smoke_fragment.glsl"
    );

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glUseProgram(d_program);
    d_color_location = glGetUniformLocation(d_program, "u_colormapping");
    d_projection_location = glGetUniformLocation(d_program, "u_transform");
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    d_drawcount = 0;
    set_size(1, 1); // dummy value
    set_color(glm::vec3(0.0f, 0.0f, 0.0f));
}
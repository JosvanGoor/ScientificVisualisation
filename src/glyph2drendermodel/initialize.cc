#include "glyph2drendermodel.ih"

void Glyph2dRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/glyph2d_vertex.glsl",
        "shaders/glyph2d_fragment.glsl"
    );
    d_projection_location = glGetUniformLocation(d_program, "projection");

    vector<float> glyph = unit_glyph();

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(glyph), glyph.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);
}


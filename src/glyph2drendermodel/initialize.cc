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

    /* X/Y transform*/
    glGenBuffers(1, &d_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    /* Rotation */
    glGenBuffers(1, &d_rotation_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_rotation_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    /* Colors */
    glGenBuffers(1, &d_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    set_glyph_dim(d_glyph_dim);
}


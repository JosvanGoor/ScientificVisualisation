#include "arrow3drendermodel.ih"
#include <iostream>

void Arrow3dRenderModel::initialize()
{

    cout << "3dArrow\n";
    cout.flush();

    d_program = build_program
    (
        "shaders/arrow3d_vertex.glsl",
        "shaders/arrow3d_fragment.glsl"
    );
    cout << "3dArrow\n";
    cout.flush();

    d_projection_location = glGetUniformLocation(d_program, "projection");

    ObjReader reader{"object_files/arrow.obj"};
    vector<float> vertices = reader.raw_vertices();
    vector<float> normals = reader.raw_normals();
    d_drawcount = vertices.size() / 3;

    glGenVertexArrays(1, &d_attribute_object);
    glBindVertexArray(d_attribute_object);

    glGenBuffers(1, &d_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(vertices), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(normals), normals.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    /* X/Y transform */
    glGenBuffers(1, &d_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    /* Rotation */
    glGenBuffers(1, &d_rotation_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_rotation_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);

    /* Scalar (color / scale) */
    glGenBuffers(1, &d_scalar_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, d_scalar_buffer);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);

    /* Cleanup */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    set_arrow_dim(d_arrow_dim);
}
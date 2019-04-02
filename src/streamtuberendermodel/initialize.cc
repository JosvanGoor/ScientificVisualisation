#include "streamtuberendermodel.ih"

void StreamtubeRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/streamtube_vs.glsl",
        "shaders/streamtube_fs.glsl"
    );

    d_lookat = glm::lookAt
    (
        glm::vec3(0.0f, -20.0f, 15.0f), // cam pos
        glm::vec3(0.0f, 0.0f, 0.0f), // center / looking at
        glm::vec3(0.0f, 0.0f, 1.0f) // up
    );

    d_projection_location = glGetUniformLocation(d_program, "projection");

    glGenVertexArrays(1, &d_attribute_buffer);
    glBindVertexArray(d_attribute_buffer);

    glGenBuffers(1, &d_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, d_vertices);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_normals);
    glBindBuffer(GL_ARRAY_BUFFER, d_normals);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/smoke3d_vs.glsl",
        "shaders/smoke3d_fs.glsl"
    );

    d_projection_loc = glGetUniformLocation(d_program, "projection");
    d_sampler_loc = glGetUniformLocation(d_program, "tex");

    // smoke part
    glGenVertexArrays(1, &d_smoke_attributes);
    glBindVertexArray(d_smoke_attributes);

    glGenBuffers(1, &d_smoke_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &d_smoke_normals);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_normals);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &d_smoke_texcoords);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_texcoords);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // build framebuffer
    
}
#include "smoke3drendermodel.ih"

void Smoke3dRenderModel::initialize()
{
    d_program = build_program
    (
        "shaders/smoke3d_vs.glsl",
        "shaders/smoke3d_fs.glsl"
    );

    d_projection_loc = glGetUniformLocation(d_program, "projection");
    d_colormapping_loc = glGetUniformLocation(d_program, "u_colormapping");
    d_limit_loc = glGetUniformLocation(d_program, "u_limits");

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

    glGenBuffers(1, &d_smoke_colors);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_colors);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), nullptr);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // bar part
    glGenVertexArrays(1, &d_bar_attributes);
    glBindVertexArray(d_bar_attributes);

    glGenBuffers(1, &d_bar_vertex);
    glBindBuffer(GL_ARRAY_BUFFER, d_bar_vertex);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // init renderfont
    d_renderfont = RenderFont{"fonts/comic.ttf", 16};
    d_mintext = d_renderfont.create_string(".", GL_STREAM_DRAW);
    d_maxtext = d_renderfont.create_string(",", GL_STREAM_DRAW);
}
#include "smokerendermodel.ih"

#include <iostream>
#include <sstream>
#include <iomanip>

void SmokeRenderModel::render_bar()
{
    float left = d_width  - 50;
    float right = d_width - 25;
    float top = d_height * 0.9;
    float bot = d_height * 0.1;

    glUseProgram(d_program);
    glBindVertexArray(d_bar_vao);

    float bigger[6][2] = 
    {
        left - 5, bot - 5, left - 5, top + 5, right + 5, top + 5,
        left - 5, bot - 5, right + 5, bot - 5, right + 5, top + 5
    };

    float white[6] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    glBindBuffer(GL_ARRAY_BUFFER, d_bar_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bigger), bigger, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, d_bar_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(white), white, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glUniform1i(d_colormapping_location, 0);
    glUniform2f(d_limit_location, 0.0, 1.0);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 2);

    float triangles[6][2] =
    {
        left, bot, left, top, right, top,
        left, bot, right, bot, right, top
    };

    float colors[6] =
    {
        d_min, d_max, d_max,
        d_min, d_min, d_max
    };

    glBindBuffer(GL_ARRAY_BUFFER, d_bar_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, d_bar_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUniformMatrix4fv(d_projection_location, 1, GL_FALSE, glm::value_ptr(d_projection));
    glUniform1i(d_colormapping_location, d_colormapping);
    glUniform2f(d_limit_location, d_min, d_max);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 2);
    glBindVertexArray(0);

    stringstream min;
    stringstream max;

    min << setprecision(2) << scientific << d_min;
    max << setprecision(2) << scientific << d_max;

    left -= 25;
    d_renderfont.update_string(d_maxtext, max.str());
    d_renderfont.update_string(d_mintext, min.str());
    d_renderfont.render_string_outlined(d_maxtext, glm::vec2{left, bot - 26});
    d_renderfont.render_string_outlined(d_mintext, glm::vec2{left, top + 10});
}
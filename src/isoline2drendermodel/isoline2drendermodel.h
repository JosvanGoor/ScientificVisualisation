#ifndef __INCLUDED_ISOLINE2DRENDERMODEL_H
#define __INCLUDED_ISOLINE2DRENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utility/utility.h"

#include <glad/glad.h>
#include <vector>

class Isoline2dRenderModel
{

    size_t d_drawcount;
    glm::vec3 d_color;
    glm::mat4 d_projection;

    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;

    GLuint d_color_location;
    GLuint d_projection_location;

    public:
        Isoline2dRenderModel();

        void render();

        void set_color(glm::vec3 const &color);
        void set_size(size_t width, size_t height);
        void update_lines(std::vector<float> const &lines);
};

inline void Isoline2dRenderModel::set_color(glm::vec3 const &color)
{
    d_color = color;
}

inline void Isoline2dRenderModel::set_size(size_t width, size_t height)
{
    d_projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

#endif
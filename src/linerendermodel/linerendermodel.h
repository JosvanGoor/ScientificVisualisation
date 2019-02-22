#ifndef __INCLUDED_LINERENDERMODEL_H
#define __INCLUDED_LINERENDERMODEL_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../rendermodel/rendermodel.h"

class LineRenderModel : public RenderModel
{
    size_t d_linecount;
    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_color_buffer;

    GLuint d_projection_location;
    glm::mat4 d_projection;

    public:
        LineRenderModel();

        void render();

        void framebuffer_size(size_t width, size_t height);
        void set_data(std::vector<float> const &lines, std::vector<float> const &colors);

    private:
        std::vector<float> default_lines();
        std::vector<float> default_colors();
};

#endif
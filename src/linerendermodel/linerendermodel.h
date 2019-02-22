#ifndef __INCLUDED_LINERENDERMODEL_H
#define __INCLUDED_LINERENDERMODEL_H

#include <vector>
#include <glm/glm.hpp>

#include "../rendermodel/rendermodel.h"

class LineRenderModel : public RenderModel
{
    size_t d_linecount;
    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_color_buffer;
    glm::mat4 d_projection;

    std::vector<float> d_lines;
    std::vector<float> d_colors;

    public:
        LineRenderModel();

        void render();

    private:
        std::vector<float> default_lines();
        std::vector<float> default_colors();
};

#endif
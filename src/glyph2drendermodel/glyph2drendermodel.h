#ifndef __INCLUDED_GLYPH2DRENDERMODEL_H
#define __INCLUDED_GLYPH2DRENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../rendermodel/rendermodel.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class Glyph2DRenderModel
{
    size_t d_framewidth;
    size_t d_frameheight;
    size_t d_glyph_dim; // # of glyphs per dimension

    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_position_buffer;
    GLuint d_rotation_buffer;
    GLuint d_scale_buffer;
    GLuint d_color_buffer;

    public:
        Glyph2DRenderModel();

    private:
        std::vector<float> unit_glyph();

        void initialize();
};

#endif
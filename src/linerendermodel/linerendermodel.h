#ifndef __INCLUDED_LINERENDERMODEL_H
#define __INCLUDED_LINERENDERMODEL_H

#include "../rendermodel/rendermodel.h"

class LineRenderModel : public RenderModel
{
    size_t d_linecount;
    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_color_buffer;

    GLuint d_projection_location;

    public:
        LineRenderModel();
        ~LineRenderModel();

        void render();

        void set_data(std::vector<float> const &lines, std::vector<float> const &colors);

    private:
        std::vector<float> default_lines();
        std::vector<float> default_colors();
};

#endif
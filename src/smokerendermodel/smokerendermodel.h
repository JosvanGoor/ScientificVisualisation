#ifndef __INCLUDED_SMOKERENDERMODEL_H
#define __INCLUDED_SMOKERENDERMODEL_H

#include "../rendermodel/rendermodel.h"

class SmokeRenderModel : public RenderModel
{

    size_t d_rows;
    size_t d_drawcount;
    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_color_buffer;
    GLuint d_projection_location;

    public:
        SmokeRenderModel(size_t d_rows = 50);
        ~SmokeRenderModel();

        void render();
        void set_data(std::vector<float> const &lines, std::vector<float> const &colors);

    private:
        std::vector<float> default_tristrip();
        std::vector<float> default_colors();

};

#endif
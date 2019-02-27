#ifndef __INCLUDED_SMOKERENDERMODEL_H
#define __INCLUDED_SMOKERENDERMODEL_H

#include "../rendermodel/rendermodel.h"

class SmokeRenderModel : public RenderModel
{
    GLuint d_bar_vao;
    GLuint d_bar_vertices;
    GLuint d_bar_colors;

    public:
        SmokeRenderModel();
        ~SmokeRenderModel();

        void render();
        void render_bar();

    private:
        void build_bar();
};

#endif
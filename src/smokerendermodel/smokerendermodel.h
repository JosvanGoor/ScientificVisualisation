#ifndef __INCLUDED_SMOKERENDERMODEL_H
#define __INCLUDED_SMOKERENDERMODEL_H

#include "../rendermodel/rendermodel.h"
#include "../renderfont/renderfont.h"

class SmokeRenderModel : public RenderModel
{
    GLuint d_bar_vao;
    GLuint d_bar_vertices;
    GLuint d_bar_colors;
    RenderFont d_renderfont;
    RenderFont::String d_maxtext;
    RenderFont::String d_mintext;
    
    public:
        SmokeRenderModel();
        ~SmokeRenderModel();

        void render();
        void render_bar();
        void framebuffer_size(size_t width, size_t height) override;

    private:
        void build_bar();
};

inline void SmokeRenderModel::framebuffer_size(size_t width, size_t height)
{
    RenderModel::framebuffer_size(width, height);
    d_renderfont.set_size(width, height);
}

#endif
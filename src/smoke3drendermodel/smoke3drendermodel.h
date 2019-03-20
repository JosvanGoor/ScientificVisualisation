#ifndef __INCLUDED_SMOKE3DRENDERMODEL_H
#define __INCLUDED_SMOKE3DRENDERMODEL_H

#include "../renderfont/renderfont.h"
#include "../utility/utility.h"

class Smoke3dRenderModel
{
    GLuint d_program;

    // background buffers
    GLuint d_smoke_attributes;
    GLuint d_smoke_vertices;
    GLuint d_smoke_normals;
    GLuint d_smoke_colors;

    // bar buffers
    GLuint d_bar_attributes;
    GLuint d_bar_vertex;
    glm::mat4 d_bar_projection;

    // extra
    float d_cmin; // color
    float d_cmax;
    float d_hmin; // height
    float d_hmax;
    size_t d_width;
    size_t d_height;
    size_t d_gridsize;
    size_t d_drawcount;
    size_t d_colormapping;
    glm::mat4 d_projection;

    // tri buffer
    std::vector<float> d_triangles;

    // uniform locations
    GLuint d_projection_loc;
    GLuint d_colormapping_loc;
    GLuint d_limit_loc;

    // text stuff
    RenderFont d_renderfont;
    RenderFont::String d_maxtext;
    RenderFont::String d_mintext;

    public:
        Smoke3dRenderModel();
        ~Smoke3dRenderModel();

        void render();
        void render_bar();

        void set_colormapping(size_t mapping);
        void set_colormap(std::vector<float> const &color, float min = 0, float max = 0);
        void set_heightmap(std::vector<float> const &color, float min = 0, float max = 0);

        void initialize();
        void set_framebuffer_size(size_t width, size_t height, size_t gridsize);

    private:
        Smoke3dRenderModel(Smoke3dRenderModel&) = delete;
        Smoke3dRenderModel &operator=(Smoke3dRenderModel&) = delete;

        // ran on resize
        std::vector<float> update_smoke_mapping(size_t gridsize);
};

inline void Smoke3dRenderModel::set_colormapping(size_t mapping)
{
    d_colormapping = mapping;
}

#endif
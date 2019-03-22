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
    GLuint d_smoke_texcoords;

    // framebuffer parts
    GLuint d_framebuffer;
    GLuint d_color_tex;
    GLuint d_depth_rbuf;

    // extra
    float d_hmin; // height
    float d_hmax;
    size_t d_width;
    size_t d_height;
    size_t d_gridsize;
    size_t d_drawcount;
    glm::mat4 d_lookat;
    glm::mat4 d_projection;
    
    // tri buffer
    std::vector<float> d_triangles;

    // uniform locations
    GLuint d_sampler_loc;
    GLuint d_projection_loc;
    
    public:
        Smoke3dRenderModel();
        ~Smoke3dRenderModel();

        void render();
        
        void bind_framebuffer();
        void release_framebuffer();

        void set_heightmap(std::vector<float> const &color, float min = 0, float max = 0);

        void initialize();
        void set_framebuffer_size(size_t width, size_t height, size_t gridsize);

    private:
        Smoke3dRenderModel(Smoke3dRenderModel&) = delete;
        Smoke3dRenderModel &operator=(Smoke3dRenderModel&) = delete;

        // ran on resize
        void generate_framebuffer();
        void update_smoke_mapping(size_t gridsize);
};

inline void Smoke3dRenderModel::bind_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, d_framebuffer);
}

inline void Smoke3dRenderModel::release_framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#endif
#ifndef __INCLUDED_RENDERMODEL_H
#define __INCLUDED_RENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <string>
#include <vector>

class RenderModel
{
    protected:
        size_t d_drawcount;
        int d_colormapping;
        float d_min, d_max;
        glm::mat4 d_projection;
        GLuint d_projection_location;
        GLuint d_colormapping_location;
        GLuint d_limit_location;

        GLuint d_program;
        GLuint d_vertex_buffer;
        GLuint d_color_buffer;
        GLuint d_attribute_object;


    public:
        RenderModel();
        virtual ~RenderModel();

        virtual void render() = 0;
        
        void set_colormapping(int mapping);
        void set_drawcount(size_t drawcount);
        void set_color_data(std::vector<float> const &colors, float v_min = 0, float v_max = 1);
        void set_vertex_data(std::vector<float> const &vertex);
        void framebuffer_size(size_t width, size_t height);

        void load_shaders(std::string const &vsfile, std::string const &fsfile);
        void prepare_buffers(size_t coord_width, size_t color_width);

    protected:
        static GLuint compile_shader(std::string const &source, GLuint type);
        static GLuint link_program(GLuint vshader, GLuint fshader);
};

inline void RenderModel::set_colormapping(int mapping)
{
    d_colormapping = mapping;
}

inline void RenderModel::set_drawcount(size_t drawcount)
{
    d_drawcount = drawcount;
}

#endif
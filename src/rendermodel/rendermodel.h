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
        glm::mat4 d_projection;

    public:
        virtual ~RenderModel();

        virtual void render() = 0;
        virtual void set_data(std::vector<float> const &vertices, std::vector<float> const &colors) = 0;
        void framebuffer_size(size_t width, size_t height);

    protected:
        static GLuint compile_shader(std::string const &source, GLuint type);
        static GLuint link_program(GLuint vshader, GLuint fshader);
};

#endif
#ifndef __INCLUDED_RENDERMODEL_H
#define __INCLUDED_RENDERMODEL_H

#include <glad/glad.h>
#include <string>

class RenderModel
{
    public:
        virtual ~RenderModel();

        virtual void render() = 0;

    protected:
        static GLuint compile_shader(std::string const &source, GLuint type);
        static GLuint link_program(GLuint vshader, GLuint fshader);
};

#endif
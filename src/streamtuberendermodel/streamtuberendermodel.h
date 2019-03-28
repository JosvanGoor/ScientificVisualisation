#ifndef __INCLUDED_STREAMTUBERENDERMODEL_H
#define __INCLUDED_STREAMTUBERENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utility/utility.h"

class StreamtubeRenderModel
{
    GLuint d_program;
    GLuint d_attribute_buffer;
    GLuint d_vertices;
    // GLuint d_normals;
    // GLuint d_colors;

    glm::mat4 d_projection;
    glm::mat4 d_lookat;
    GLuint d_projection_location;

    public:
        // StreamtubeRenderModel();

        void initialize();
        void set_framebuffer_size(size_t width, size_t height);

        void draw_lines(std::vector<float> const &lines, size_t nlayers);

    private:
};

#endif
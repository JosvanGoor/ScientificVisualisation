#ifndef __INCLUDED_GLYPH2DRENDERMODEL_H
#define __INCLUDED_GLYPH2DRENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../rendermodel/rendermodel.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class Glyph2dRenderModel
{
    size_t d_glyph_dim; // # of glyphs per dimension

    glm::mat4 d_lookat;
    glm::mat4 d_projection;
    GLuint d_projection_location;

    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_position_buffer;
    GLuint d_rotation_buffer;
    GLuint d_color_buffer;

    public:
        Glyph2dRenderModel();
        
        void render();
        void render_2d();

        void set_framebuffer_size(size_t width, size_t height);

        void set_glyph_dim(size_t dim);
        void update_scalar(std::vector<double> const &scalar, size_t gridsize);
        void update_vectors(double *vecx, double *vecy, size_t gridsize);
        void update_vectors(std::vector<double> &vecx, std::vector<double> &vecy, size_t gridsize);
        void initialize();

    private:
        std::vector<float> unit_glyph();

};

#endif
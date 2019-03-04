#ifndef __INCLUDED_ARROWRENDERMODEL_H
#define __INCLUDED_ARROWRENDERMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utility/utility.h"

#include <glad/glad.h>
#include <string>
#include <vector>

class Arrow3dRenderModel
{
    size_t d_drawcount;
    size_t d_arrow_dim;
    size_t d_arrow_detail;

    glm::mat4 d_projection; //includes lookat
    GLuint d_projection_location;

    GLuint d_program;
    GLuint d_attribute_object;
    GLuint d_vertex_buffer;
    GLuint d_normal_buffer;
    GLuint d_position_buffer;
    GLuint d_rotation_buffer;
    GLuint d_scalar_buffer;

    public:
        Arrow3dRenderModel();

        void render();

        void set_arrow_dim(size_t dim);
        void update_scalar(std::vector<double> const &scalar, size_t gridsize);
        void update_vectors(double *vecx, double *vecy, size_t gridsize);
        void update_vectors(std::vector<double> &vecx, std::vector<double> &vecy, size_t gridsize);

    private:
        std::vector<float> unit_arrow(size_t detail);
        std::vector<float> unit_arrow_normals(std::vector<float> const &vertices);
        void initialize();
};

#endif
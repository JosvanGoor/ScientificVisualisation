#include "arrow3drendermodel.ih"

Arrow3dRenderModel::Arrow3dRenderModel()
:   d_arrow_dim(50),
    d_arrow_detail(300),
    d_projection(1),
    d_program(0),
    d_attribute_object(0),
    d_vertex_buffer(0),
    d_position_buffer(0),
    d_rotation_buffer(0),
    d_scalar_buffer(0)
{
    //* Gonna use some "magic" settings here
    //* They are sound, I calculated them on paper
    //* After these transforms the plane at 0,0,0 spans ~83x83 which
    //* scales the arrows at a decent size
    //* we also want to know the size of the plane so we can 
    //* map them over the 2d simulation grid
    glm::mat4 projection = glm::perspective(radians(90.0f), 3.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 lookat = glm::lookAt
    (
        glm::vec3(0.0f, 0.0f, 83.0f / 2.0f), // yes
        glm::vec3(0.0f, 0.0f, 0.0f), // trust me
        glm::vec3(0.0f, 1.0f, 0.0f) // it works
    );
    d_projection = projection * lookat;

    initialize();
    set_arrow_dim(d_arrow_dim);
}
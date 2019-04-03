#include "window.ih"

glm::vec3 Window::unproject_mouse() const
{
    // get screen space coordinates
    glm::vec4 ray_clip = glm::vec4
    {
        (2.0f * d_mouse_zx) / d_width - 1.0f,
        1.0f - (2.0f * d_mouse_zy) / d_height,
        -1.0f, // we assume we look towards negative z
        1.0f
    };

    // inverse the projection
    glm::vec4 ray_eye = glm::inverse(d_smoke3d.projection()) * ray_clip;
    // we're still looking towards negative z
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    
    // inverse lookat, and normalize
    glm::vec3 ray_world = glm::vec3(glm::inverse(d_smoke3d.lookat()) * ray_eye);
    ray_world = normalize(ray_world);

    // calculate z-plane difference from camera location    
    const glm::vec3 cam_pos = glm::vec3(0.0f, -20.0f, 15.0f);
    float zsteps = -cam_pos.z / ray_world.z;

    // calculate position at z ~= 0.0.
    glm::vec3 pos = cam_pos + (zsteps * ray_world);

    return pos;
}
#include "renderfont.ih"

glm::vec2 RenderFont::tex_position(size_t width, size_t height, size_t xpos, size_t ypos)
{
    return glm::vec2
    {
        static_cast<float>(xpos) / static_cast<float>(width),
        static_cast<float>(ypos) / static_cast<float>(height)
    };
}
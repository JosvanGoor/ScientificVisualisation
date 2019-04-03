#include "window.ih"

#include <iostream>

void Window::mouse_button_event(int button, int action, int mods)
{
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS)
                d_mouse_dragging = true;
            else
                d_mouse_dragging = false;
        break;

        case GLFW_MOUSE_BUTTON_RIGHT:
        {
            if (d_drawmode != DrawMode::SMOKE3D)
                return;

            // prevent we place 2 in 1 click.
            if (action != GLFW_PRESS)
                return;

            glm::vec3 pos = unproject_mouse();

            // if the coordinates fall outside of the grid we ignore them
            if (abs(pos.x) >= 10.0 || abs(pos.y) >= 10.0)
                return;

            d_streamline_anchors.push_back(glm::vec3
            {
                ((pos.x + 10.0) / 20.0),
                ((pos.y + 10.0) / 20.0),
                0.0f
            });
        }
        break;

        default: break;
    }

}
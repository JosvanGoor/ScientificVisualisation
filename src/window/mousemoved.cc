#include "window.ih"

#include <iostream>

void Window::mouse_moved(double xpos, double ypos)
{
    d_mouse_zx = xpos;
    d_mouse_zy = ypos;

    if (!d_mouse_dragging)
        return;

    // If we render in 3d we need to unproject the mouse and 
    // translate the coordinates to screen space.
    if (d_drawmode == DrawMode::SMOKE3D || d_drawmode == DrawMode::STREAMTUBES)
    {
        glm::vec3 world_pos = unproject_mouse();

        // if the coordinates fall outside of the grid we ignore them
        if (abs(world_pos.x) >= 10.0 || abs(world_pos.y) >= 10.0)
            return;

        xpos = ((world_pos.x + 10.0) / 20.0) * d_width;
        ypos = (1.0 - ((world_pos.y + 10.0) / 20.0)) * d_height;
    }

    double fix_x = d_width / static_cast<double>(d_simulation.gridsize() + 1) + 5;
    double fix_y = d_height / static_cast<double>(d_simulation.gridsize() + 1) + 5;
    
    xpos = xpos > fix_x ? xpos : fix_x;
    xpos = xpos < d_width - fix_x ? xpos : fix_x;
    ypos = ypos > fix_y ? ypos : fix_y;
    ypos = ypos < d_height - fix_y ? ypos : fix_y;

    int xi = clamp((d_simulation.gridsize() + 1) * (xpos / d_width));
    int yi = clamp((d_simulation.gridsize() + 1) * ((d_height - ypos) / d_height));

    int X = xi; //?
    int Y = yi; //??

    if (X > (d_simulation.gridsize() - 1))
        X = d_simulation.gridsize() - 1;
    if (Y > (d_simulation.gridsize() - 1))
        Y = d_simulation.gridsize() - 1;
    if (X < 0) X = 0;
    if (Y < 0) Y = 0;

    ypos = d_height - ypos;
    double dx = xpos - d_mouse_lastx;
    double dy = ypos - d_mouse_lasty;
    double len = sqrt(dx * dx + dy * dy);
    if (len != 0.0) //shouldnt ever be false lol
    {
        dx *= 0.1 / len;
        dy *= 0.1 / len;
    }
    else
        cout << "the comment is wrong!\n";

    size_t pos = Y * d_simulation.gridsize() + X;
    d_simulation.force_x()[pos] += dx;
    d_simulation.force_y()[pos] += dy;
    d_simulation.rho()[pos] = 10.0f;

    d_mouse_lastx = xpos;
    d_mouse_lasty = ypos;    
}
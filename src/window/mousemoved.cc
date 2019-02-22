#include "window.ih"

#include <iostream>

void Window::mouse_moved(double xpos, double ypos)
{
    if (!d_mouse_dragging)
        return;

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

    double xval = 0;
    double yval = 0;
    for (size_t idx = 0; idx < d_simulation.gridsize() * d_simulation.gridsize(); ++idx)
    {
        xval += d_simulation.force_x()[idx];
        yval += d_simulation.force_y()[idx];
    }

    cout << "xval: " << xval << ", yval: " << yval << "\n";

    d_mouse_lastx = xpos;
    d_mouse_lasty = ypos;    
}
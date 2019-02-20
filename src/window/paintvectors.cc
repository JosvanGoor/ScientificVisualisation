#include "window.ih"

void Window::paint_vectors(Simulation const &sim)
{
    double wn = d_width / static_cast<double>(sim.gridsize() + 1);
    double hn = d_height / static_cast<double>(sim.gridsize() + 1);

    glBegin(GL_LINES);

    for (int idx = 0; idx < sim.gridsize(); ++idx)
    {
        for (int jdx = 0; jdx < sim.gridsize(); ++jdx)
        {
            int index = jdx * sim.gridsize() + idx;

            direction_to_color(sim.vfield_x()[index], sim.vfield_y()[index]);
            glVertex2f(wn + idx * wn, hn + jdx * hn);
            glVertex2f
            (
                (wn + idx * wn) + d_vec_scale * sim.vfield_x()[index],
                (hn + jdx * hn) + d_vec_scale * sim.vfield_y()[index]
            );
        }
    }

    glEnd();
}
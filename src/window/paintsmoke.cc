#include "window.ih"

void Window::paint_smoke(Simulation const &sim)
{
    double wn = d_width / static_cast<double>(sim.gridsize() + 1);
    double hn = d_height / static_cast<double>(sim.gridsize() + 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    for (int jdx = 0; jdx < (sim.gridsize() - 1); ++jdx)
    {
        glBegin(GL_TRIANGLE_STRIP);

        int idx = 0;
        float px = wn + idx * wn; // think about this...
        float py = hn + jdx * hn;
        int index = jdx * sim.gridsize() + idx;

        glColor3f(sim.rho()[index], sim.rho()[index], sim.rho()[index]);
        glVertex2f(px, py);

        for (; idx < sim.gridsize(); ++idx)
        {
            px = wn + idx * wn;
            py = hn + (jdx + 1) * hn;
            index = ((jdx + 1) * sim.gridsize()) + idx;
            set_colormap(sim.rho()[index]);
            glVertex2f(px, py);

            px = wn + (idx + 1) * wn;
            py = hn + jdx * hn;
            index = (jdx * sim.gridsize()) + (idx + 1);
            set_colormap(sim.rho()[index]);
            glVertex2f(px, py);
        }

        px = wn + (sim.gridsize() - 1) * wn;
        py = hn + (jdx + 1) * hn;
        index = ((jdx + 1) * sim.gridsize()) + (sim.gridsize() - 1);
        set_colormap(sim.rho()[index]);
        glVertex2f(px, py);

        glEnd();
    }
}
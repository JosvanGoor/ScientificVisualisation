#include "window.ih"

#include <iostream>

void Window::paint_vectors()
{
    double wn = d_width / static_cast<double>(d_simulation.gridsize() + 1);
    double hn = d_height / static_cast<double>(d_simulation.gridsize() + 1);

    std::vector<float> lines;
    std::vector<float> colors;

    lines.reserve(4 * (d_simulation.gridsize() * d_simulation.gridsize()));
    colors.reserve(4 * (d_simulation.gridsize() * d_simulation.gridsize()));

    for (int idx = 0; idx < d_simulation.gridsize(); ++idx)
    {
        for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
        {
            int index = jdx * d_simulation.gridsize() + idx;

            // line start
            lines.push_back(wn + idx * wn);
            lines.push_back(hn + jdx * hn);
            
            //line end
            lines.push_back((wn + idx * wn) + d_vec_scale * d_simulation.vfield_x()[index]);
            lines.push_back((hn + jdx * hn) + d_vec_scale * d_simulation.vfield_y()[index]);

            //color for both points
            colors.push_back(d_simulation.vfield_x()[index]);
            colors.push_back(d_simulation.vfield_y()[index]);
            colors.push_back(d_simulation.vfield_x()[index]);
            colors.push_back(d_simulation.vfield_y()[index]);
        }
    }

    d_rendermodel->set_color_data(colors);
    d_rendermodel->set_vertex_data(lines);
    d_rendermodel->set_drawcount(lines.size() / 2);
    d_rendermodel->render();
}
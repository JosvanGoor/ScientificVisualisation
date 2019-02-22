#include "window.ih"

#include <iostream>

void Window::paint_vectors()
{
    double wn = d_width / static_cast<double>(d_simulation.gridsize() + 1);
    double hn = d_height / static_cast<double>(d_simulation.gridsize() + 1);

    std::vector<float> lines;
    std::vector<float> colors;

    for (int idx = 0; idx < d_simulation.gridsize(); ++idx)
    {
        for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
        {
            int index = jdx * d_simulation.gridsize() + idx;

            Color col = direction_to_color
            (
                d_simulation.vfield_x()[index],
                d_simulation.vfield_y()[index]
            );

            // line start
            lines.push_back(wn + idx * wn);
            lines.push_back(hn + jdx * hn);
            
            //line end
            lines.push_back((wn + idx * wn) + d_vec_scale * d_simulation.vfield_x()[index]);
            lines.push_back((hn + jdx * hn) + d_vec_scale * d_simulation.vfield_y()[index]);

            //color for both points
            colors.insert(colors.end(), col.begin(), col.end());
            colors.insert(colors.end(), col.begin(), col.end());
        }
    }

    d_rendermodel->set_data(lines, colors);
    d_rendermodel->render();
}
#include "window.ih"

#include <iostream>

void Window::paint_vectors()
{
    double wn = d_width / static_cast<double>(d_simulation.gridsize() + 1);
    double hn = d_height / static_cast<double>(d_simulation.gridsize() + 1);
    
    if (omp_get_thread_num() == 0)
    {   
        colors_lines.resize(4 * d_simulation.gridsize() * d_simulation.gridsize(), 0);
        lines.resize(4 * d_simulation.gridsize() * d_simulation.gridsize(), 0);
    }

    #pragma omp barrier
    #pragma omp for
    for (int idx = 0; idx < d_simulation.gridsize(); ++idx)
    {
        int line = idx * 4 * d_simulation.gridsize();
        for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
        {
            int index = jdx * d_simulation.gridsize() + idx;

            // line start
            colors_lines[line] = (wn + idx * wn);
            colors_lines[line + 1] = (hn + jdx * hn);
            
            //line end
            colors_lines[line + 2] = ((wn + idx * wn) + d_vec_scale * d_simulation.vfield_x()[index]);
            colors_lines[line + 3] = ((hn + jdx * hn) + d_vec_scale * d_simulation.vfield_y()[index]);

            //color for both points
            colors[line] = (d_simulation.vfield_x()[index]);
            colors[line + 1] = (d_simulation.vfield_y()[index]);
            colors[line + 2] = (d_simulation.vfield_x()[index]);
            colors[line + 3] = (d_simulation.vfield_y()[index]);
            
            line += 4;
        }
    }

    #pragma omp barrier
    if (omp_get_thread_num() == 0)
    {
        d_rendermodel->set_color_data(colors);
        d_rendermodel->set_vertex_data(colors_lines);
        d_rendermodel->set_drawcount(colors_lines.size() / 2);
        d_rendermodel->render();
    }
    #pragma omp barrier
}
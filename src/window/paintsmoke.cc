#include "window.ih"

#include <chrono>
#include <iostream>

void Window::paint_smoke()
{
    vector<float> colors;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    chrono::time_point t1 = chrono::high_resolution_clock::now();
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
        int index = jdx * d_simulation.gridsize();
        colors.push_back(d_simulation.rho()[index]);
        
        for (int idx = 0; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            index = ((jdx + 1) * d_simulation.gridsize()) + idx;
            colors.push_back(d_simulation.rho()[index]);
            
            index = (jdx * d_simulation.gridsize()) + (idx + 1);
            colors.push_back(d_simulation.rho()[index]);
        }

        index = ((jdx + 1) * d_simulation.gridsize()) + (d_simulation.gridsize() - 1);
        colors.push_back(d_simulation.rho()[index]);
    }
    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s preparing\n";
    t1 = chrono::high_resolution_clock::now();
    d_rendermodel->set_color_data(colors);
    d_rendermodel->render();
    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s rendering\n";
}
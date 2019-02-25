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
        int idx = 0;
        int index = jdx * d_simulation.gridsize() + idx;

        Color col = colormap(d_simulation.rho()[index]);
        colors.insert(colors.end(), col.begin(), col.end());
        
        for (; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            index = ((jdx + 1) * d_simulation.gridsize()) + idx;
            col = colormap(static_cast<float>(d_simulation.rho()[index]));
            colors.insert(colors.end(), col.begin(), col.end());
            
            index = (jdx * d_simulation.gridsize()) + (idx + 1);
            col = colormap(static_cast<float>(d_simulation.rho()[index]));
            colors.insert(colors.end(), col.begin(), col.end());
        }

        index = ((jdx + 1) * d_simulation.gridsize()) + (d_simulation.gridsize() - 1);
        col = colormap(static_cast<float>(d_simulation.rho()[index]));
        colors.insert(colors.end(), col.begin(), col.end());
    }
    cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s preparing\n";
    t1 = chrono::high_resolution_clock::now();
    d_rendermodel->set_color_data(colors);
    d_rendermodel->render();
    cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s rendering\n";
}
#include "window.ih"

#include <chrono>
#include <algorithm>
#include <iostream>
#include <cmath>

fftw_real length(fftw_real a, fftw_real b)
{   
    return std::sqrt(a * a + b * b);
}

void Window::paint_smoke()
{
    vector<float> colors;
    colors.reserve(2 * d_simulation.gridsize() * d_simulation.gridsize());
    
    vector<fftw_real> store;

    switch (d_colormode)
    {
        case ColorMode::DENSITY:
            store.reserve(d_simulation.rho().size());
            std::copy(d_simulation.rho().begin(), d_simulation.rho().end(), store.begin());
            break;
        case ColorMode::VELOCITY:
            store.reserve(d_simulation.vfield_x().size());
            std::transform(d_simulation.vfield_x().begin(),d_simulation.vfield_x().end(),
                            d_simulation.vfield_y().begin(), store.begin(), length);
            break;
        case ColorMode::FORCE:
            store.reserve(d_simulation.force_x().size());
            std::transform(d_simulation.force_x().begin(),d_simulation.force_x().end(),
                            d_simulation.force_y().begin(), store.begin(), length);
            break;
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // chrono::time_point t1 = chrono::high_resolution_clock::now();
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
        int index = jdx * d_simulation.gridsize();
        colors.push_back(store[index]);
        
        for (int idx = 0; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            index = ((jdx + 1) * d_simulation.gridsize()) + idx;
            colors.push_back(store[index]);
            
            index = (jdx * d_simulation.gridsize()) + (idx + 1);
            colors.push_back(store[index]);
        }

        index = ((jdx + 1) * d_simulation.gridsize()) + (d_simulation.gridsize() - 1);
        colors.push_back(store[index]);
    }

    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s preparing\n";
    // t1 = chrono::high_resolution_clock::now();
    d_rendermodel->set_color_data(colors);
    d_rendermodel->render();
    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s rendering\n";
}
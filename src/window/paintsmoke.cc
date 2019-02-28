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
    colors.resize(2 * d_simulation.gridsize() * d_simulation.gridsize(), 0);
    float v_min = std::numeric_limits<float>::max();
    float v_max = std::numeric_limits<float>::min();
    vector<fftw_real> store;

    // chrono::time_point t1 = chrono::high_resolution_clock::now();
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

    size_t pushloc = 0;
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
        int index = jdx * d_simulation.gridsize();
        colors[pushloc++] = (store[index]);
        
        v_max = store[index] > v_max ? store[index] : v_max;
        v_min = store[index] < v_min ? store[index] : v_min;

        for (int idx = 0; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            index = ((jdx + 1) * d_simulation.gridsize()) + idx;
            colors[pushloc++] = (store[index]);
        
            v_max = store[index] > v_max ? store[index] : v_max;
            v_min = store[index] < v_min ? store[index] : v_min;
                
            index = (jdx * d_simulation.gridsize()) + (idx + 1);
            colors[pushloc++] = (store[index]);
            
            v_max = store[index] > v_max ? store[index] : v_max;
            v_min = store[index] < v_min ? store[index] : v_min;
        }

        index = ((jdx + 1) * d_simulation.gridsize()) + (d_simulation.gridsize() - 1);
        colors[pushloc++] = (store[index]);
        
        v_max = store[index] > v_max ? store[index] : v_max;
        v_min = store[index] < v_min ? store[index] : v_min;
    }

    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s preparing\n";
    // t1 = chrono::high_resolution_clock::now();


    if (d_scalingmode == ScalingMode::STATIC)
    {
        v_min = d_min;
        v_max = d_max;
    }

    if (v_min == v_max)
    {
        v_min = v_max - 0.0000000000001;
    }

    d_rendermodel->set_color_data(colors, v_min, v_max);
    d_rendermodel->render();
    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s rendering\n";
}
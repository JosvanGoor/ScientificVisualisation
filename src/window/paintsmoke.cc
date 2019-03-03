#include "window.ih"

#include <chrono>
#include <algorithm>
#include <iostream>
#include <cmath>

double length(double a, double b)
{   
    return std::sqrt(a * a + b * b);
}

void Window::paint_smoke()
{
    #pragma omp barrier
    if (omp_get_thread_num() == 0)
    {
        colors.resize(2 * d_simulation.gridsize() * d_simulation.gridsize(), 0);
        v_min = std::numeric_limits<float>::max();
        v_max = std::numeric_limits<float>::min();

        // chrono::time_point t1 = chrono::high_resolution_clock::now();
    
        switch (d_colormode)
        {
            case ColorMode::DENSITY:
                store.resize(d_simulation.rho().size(),0);
                std::copy(d_simulation.rho().begin(), d_simulation.rho().end(), store.begin());
                break;
            case ColorMode::VELOCITY:
                store.resize(d_simulation.gridsize() * 2 * (d_simulation.gridsize() / 2 + 1),0);
                std::transform(d_simulation.vfield_x(),d_simulation.vfield_x() + d_simulation.gridsize() * 2 * (d_simulation.gridsize() / 2 + 1),
                                d_simulation.vfield_y(), store.begin(), length);
                break;
            case ColorMode::FORCE:
                store.resize(d_simulation.force_x().size(),0);
                std::transform(d_simulation.force_x().begin(),d_simulation.force_x().end(),
                                d_simulation.force_y().begin(), store.begin(), length);
                break;
            case ColorMode::MODULO_VALUE:
                throw "Invalid color mode."s;
        }

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    //local to thread
    float l_min = std::numeric_limits<float>::max();
    float l_max = std::numeric_limits<float>::min();
    #pragma omp barrier
    #pragma omp for
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
        size_t pushloc = jdx * d_simulation.gridsize() * 2;
        int index = jdx * d_simulation.gridsize();
        colors[pushloc++] = (store[index]);
        
        l_max = store[index] > l_max ? store[index] : l_max;
        l_min = store[index] < l_min ? store[index] : l_min;

        for (int idx = 0; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            int index1 = index + d_simulation.gridsize() + idx;
            colors[pushloc++] = (store[index1]);
        
            l_max = store[index1] > l_max ? store[index1] : l_max;
            l_min = store[index1] < l_min ? store[index1] : l_min;
                
            index1 = index + (idx + 1);
            colors[pushloc++] = (store[index1]);
            
            l_max = store[index1] > l_max ? store[index1] : l_max;
            l_min = store[index1] < l_min ? store[index1] : l_min;
        }
        index = index + (2 * d_simulation.gridsize());
        colors[pushloc++] = (store[index]);
        
        l_max = store[index] > l_max ? store[index] : l_max;
        l_min = store[index] < l_min ? store[index] : l_min;
    }

    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s preparing\n";
    // t1 = chrono::high_resolution_clock::now();

    #pragma omp critical
    {
        v_max = max(v_max,l_max);
        v_min = min(v_min,l_min);
    }

    #pragma omp barrier
    if (omp_get_thread_num() == 0)
    {
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
    }
    // cout << "spent " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() << " s rendering\n";
}
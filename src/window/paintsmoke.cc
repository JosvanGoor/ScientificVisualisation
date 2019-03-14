#include "window.ih"

#include <chrono>
#include <algorithm>
#include <iostream>
#include <cmath>

void Window::paint_smoke()
{
    vector<float> colors;
    colors.resize(2 * d_simulation.gridsize() * d_simulation.gridsize(), 0);
    float v_min = std::numeric_limits<float>::max();
    float v_max = std::numeric_limits<float>::lowest();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // deze kan weg denk ik

    size_t pushloc = 0;
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {

        int index = jdx * d_simulation.gridsize();
        colors[pushloc++] = (store[index]);
        
        v_max = store[index] > v_max ? store[index] : v_max;
        v_min = store[index] < v_min ? store[index] : v_min;

        for (int idx = 0; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            int index1 = index + d_simulation.gridsize() + idx;
            colors[pushloc++] = (store[index1]);
        
            v_max = store[index1] > v_max ? store[index1] : v_max;
            v_min = store[index1] < v_min ? store[index1] : v_min;
                
            index1 = index + (idx + 1);
            colors[pushloc++] = (store[index1]);
            
            v_max = store[index1] > v_max ? store[index1] : v_max;
            v_min = store[index1] < v_min ? store[index1] : v_min;
        }

        index = index + (2 * d_simulation.gridsize() - 1);
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
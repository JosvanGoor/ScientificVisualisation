#include "simulation.ih"
#include <iostream>
#include <omp.h>
#include <chrono>

template <int Size>
void Simulation<Size>::simulation_step()
{
    if(!d_running)
        return;
    // chrono::time_point t1 = chrono::high_resolution_clock::now();
    // if (omp_get_thread_num() == 0)
    //     t1 = chrono::high_resolution_clock::now();
    
    set_forces();
    // if (omp_get_thread_num() == 0)
    // {
    //     cout << "set_forces: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
    //     t1 = chrono::high_resolution_clock::now();
    // }

    solve();
    // if (omp_get_thread_num() == 0)
    // {
    //     cout << "solve: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
    //     t1 = chrono::high_resolution_clock::now();
    // }
    diffuse_matter();
    // if (omp_get_thread_num() == 0)
    //     cout << "diffuse_matter: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
}

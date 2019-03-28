#include "simulation.ih"
#include <iostream>
#include <omp.h>
#include <chrono>

template <int Size>
void Simulation<Size>::update_history()
{
    if (omp_get_thread_num() == 0)
    {
        d_history_x.push_front(d_history_x.back());
        d_history_x.pop_back();
        
        d_history_y.push_front(d_history_y.back());
        d_history_y.pop_back();
    }
    #pragma omp barrier

    #pragma omp for
    for (size_t idx = 0; idx < d_vfield_size; ++idx)
    {
        d_history_x[0][idx] = d_vfield_x[idx];
        d_history_y[0][idx] = d_vfield_y[idx];
    }
}

#include "window.ih"


double length(double a, double b)
{   
    return std::sqrt(a * a + b * b);
}

void Window::calcStore()
{
    switch (d_scalar_mode)
    {
        case ColorMode::DENSITY:
            if(omp_get_thread_num() == 0)
                store.resize(d_simulation.rho().size());
            
            #pragma omp barrier

            #pragma omp for
            for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
            {
                size_t jOff = d_simulation.gridsize() * jdx;
                
                std::copy(d_simulation.rho().begin() + jOff, d_simulation.rho().begin() + jOff + d_simulation.gridsize(), store.begin() + jOff);
            }

            break;
        case ColorMode::VELOCITY:
            if(omp_get_thread_num() == 0)
                store.resize(d_simulation.gridsize() * 2 * (d_simulation.gridsize() / 2 + 1));
            
            #pragma omp barrier   
            if (d_divmode == DivMode::OFF)
            {
                #pragma omp for
                for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
                {
                    size_t jOff = 2 * (d_simulation.gridsize() / 2 + 1) * jdx;
                    
                    std::transform(d_simulation.history_x()[19] + jOff,d_simulation.history_x()[19] + jOff + d_simulation.gridsize() + 2,
                                        d_simulation.history_y()[19] + jOff, store.begin() + jOff, length);
                }
            }
            else
                divergence<double *>(d_simulation.vfield_x(), d_simulation.vfield_y());
            #pragma omp barrier
            break;
        case ColorMode::FORCE:
            if(omp_get_thread_num() == 0)
                store.resize(d_simulation.force_x().size());

            #pragma omp barrier
            if (d_divmode == DivMode::OFF)
            {     
                #pragma omp for
                for (int jdx = 0; jdx < d_simulation.gridsize(); ++jdx)
                {
                    size_t jOff = d_simulation.gridsize() * jdx;
                    
                    std::transform(d_simulation.force_x().begin() + jOff,d_simulation.force_x().begin() + jOff + d_simulation.gridsize(),
                                        d_simulation.force_y().begin() + jOff, store.begin() + jOff, length);
                }
            
            }
            else
                divergence<vector<double>>(d_simulation.force_x(), d_simulation.force_y());
            
            #pragma omp barrier
            break;
            
        default:
            throw "Illegal colormode"s;
    }
}

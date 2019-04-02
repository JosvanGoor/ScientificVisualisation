#include "simulation.ih"
#include <omp.h>

// voor de duidelijkheid list ik de approximate regelnummers uit de
// solve.cc file

template <int Size>
void Simulation<Size>::solve()
{
    constexpr int gridsize_sq = Size * Size;

    // solve.cc: 9
    {

        // chrono::time_point t1 = chrono::high_resolution_clock::now();
        // if (omp_get_thread_num() == 0)
        //     t1 = chrono::high_resolution_clock::now();
    
        #pragma omp for
        for (int idx = 0; idx < gridsize_sq; ++idx)
        {
            d_vfield_x[idx] += d_timestep * d_force_x[idx];
            d_vfield0_x[idx] = d_vfield_x[idx];

            d_vfield_y[idx] += d_timestep * d_force_y[idx];
            d_vfield0_y[idx] = d_vfield_y[idx];
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     cout << "Time_step: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 12
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            // deze zat in de for, eruitgehaald.
            double yval = jdx * (1.0 / Size);

            size_t jOff = Size * jdx;
            double xval = 0;
            for (int idx = 0; idx != Size; ++idx)
            {
                size_t pos = idx + jOff;

                double x0 = Size * (xval - d_timestep * d_vfield0_x[pos]);
                double y0 = Size * (yval - d_timestep * d_vfield0_y[pos]);
                int i0 = clamp(x0);
                double s = x0 - i0;
                i0 = (i0 + Size) % Size; 
                int i1 = (i0 + 1) % Size;
                int j0 = clamp(y0);
                double t = y0 - j0;
                j0 = (j0  + Size) % Size; 
                int j1 = (j0 + 1) % Size;

                size_t pos00 = i0 + Size * j0;
                size_t pos01 = i0 + Size * j1;
                size_t pos10 = i1 + Size * j0;
                size_t pos11 = i1 + Size * j1;
                // solve.cc 23
                d_vfield_x[pos] = (1 - s) * ((1 - t) * d_vfield0_x[pos00] + t * d_vfield0_x[pos01])
                    + s * ((1 - t) * d_vfield0_x[pos10] + t * d_vfield0_x[pos11]);
                // solve.cc 24
                d_vfield_y[pos] = (1 - s) * ((1 - t) * d_vfield0_y[pos00] + t * d_vfield0_y[pos01])
                    + s * ((1 - t) * d_vfield0_y[pos10] + t * d_vfield0_y[pos11]);
                xval += (1.0 / Size);
            }
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     // cout << "Vfield1: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 27
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            size_t j1 = (Size + 2) * jdx;
            size_t j2 = Size * jdx;
            // for (int idx = 0; idx != Size; ++idx)
            // {
            //     d_vfield0_x[j1 + idx] = d_vfield_x[j2 + idx];
            //     d_vfield0_y[j1 + idx] = d_vfield_y[j2 + idx];
            // }
            std::copy(d_vfield_x + j2, d_vfield_x + j2 + Size, d_vfield0_x + j1);
            std::copy(d_vfield_y + j2, d_vfield_y + j2 + Size, d_vfield0_y + j1);
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     cout << "Vfield2: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 31
        // this is some hacky shit I dont even
        #pragma omp sections
        {
            {fftw_execute(d_plan_rtoc_x);}
            #pragma omp section
            {fftw_execute(d_plan_rtoc_y);}
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     cout << "FFTW first: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }
        
        // solve.cc 34
        #pragma omp for
        for (int idx = 0; idx <= Size; idx += 2)
        {
            double xval = idx * 0.5;
            double x2 = xval * xval;
            for (int jdx = 0, pos0 = idx, pos1 = idx + 1; jdx != Size; ++jdx, pos0 += (Size+2), pos1 += (Size+2))
            {
                double yval = jdx <= (Size / 2) ? jdx : (jdx - Size);
                double y2 = yval * yval;

                double r = x2 + y2;
                
                if (r == 0.0)
                    continue;


                double xy = xval * yval;

                double f = exp(-r * d_timestep * d_viscosity);

                double U[2]; //there obviously is no better way of doing this.
                double V[2];

                U[0] = d_vfield0_x[pos0];
                U[1] = d_vfield0_x[pos1];
                V[0] = d_vfield0_y[pos0];
                V[1] = d_vfield0_y[pos1];


                d_vfield0_x[pos0] = f * ((1 - x2 / r) * U[0] - xy / r * V[0]);
                d_vfield0_x[pos1] = f * ((1 - x2 / r) * U[1] - xy / r * V[1]);
                d_vfield0_y[pos0] = f * (-xy / r * U[0] + (1 - y2 / r) * V[0]);
                d_vfield0_y[pos1] = f * (-xy / r * U[1] + (1 - y2 / r) * V[1]);
            }
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     cout << "vfield 3: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 53
        // Sanity restored


       
        #pragma omp sections
        {
            {fftw_execute(d_plan_ctor_x);}
            #pragma omp section
            {fftw_execute(d_plan_ctor_y);}
        }

        // if (omp_get_thread_num() == 0)
        // {
        //     cout << "fftw second: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }
        #pragma omp barrier

        //solve.cc 56
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            size_t y1 = Size * jdx;
            size_t y2 = (Size + 2) * jdx;     
               
            for (int idx = 0; idx != Size; ++idx)
            {
                d_vfield_x[idx + y1] = d_vfield0_x[idx + y2] / (gridsize_sq);
                d_vfield_y[idx + y1] = d_vfield0_y[idx + y2] / (gridsize_sq);
            }
        }

        // if (omp_get_thread_num() == 0)
        //     cout << "v_field normalize: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<"\n\n";
    }
}

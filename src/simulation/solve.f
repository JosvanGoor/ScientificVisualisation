#include "simulation.ih"
#include <omp.h>

// voor de duidelijkheid list ik de approximate regelnummers uit de
// solve.cc file

template <int Size>
void Simulation<Size>::solve()
{
    constexpr int gridsize_sq = Size * Size;

    // cout << accumulate(d_vfield0_x.begin(), d_vfield0_x.end(), 0.0) << "\n";

    // solve.cc: 9
    {

        chrono::time_point t1 = chrono::high_resolution_clock::now();
        // if (omp_get_thread_num() == 0)
        //     t1 = chrono::high_resolution_clock::now();
    
        #pragma omp for simd
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
        //     // t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 12
        double yval, xval, x0, y0, s, t;
        int j1, i0, i1, j0;
        size_t pos, pos00, pos01, pos10, pos11, jOff;
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            // deze zat in de for, eruitgehaald.
            yval = (0.5 / Size) + jdx * (1.0 / Size);

            jOff = Size * jdx;
            xval = (0.5 / Size);
            for (int idx = 0; idx != Size; ++idx)
            {
                pos = idx + jOff;

                x0 = Size * (xval - d_timestep * d_vfield0_x[pos]) - 0.5;
                y0 = Size * (yval - d_timestep * d_vfield0_y[pos]) - 0.5;
                i0 = clamp(x0);
                s = x0 - i0;
                i0 = ((i0 % Size) + Size) % Size; 
                i1 = (i0 + 1) % Size;
                j0 = clamp(y0);
                t = y0 - j0;
                j0 = ((j0 % Size) + Size) % Size; 
                j1 = (j0 + 1) % Size;

                pos00 = i0 + Size * j0;
                pos01 = i0 + Size * j1;
                pos10 = i1 + Size * j0;
                pos11 = i1 + Size * j1;
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
        //     cout << "Vfield1: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
        //     t1 = chrono::high_resolution_clock::now();
        // }

        // solve.cc 27
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            size_t j1 = (Size + 2) * jdx;
            size_t j2 = Size * jdx;

            for (int idx = 0; idx != Size; ++idx)
            {
                d_vfield0_x[idx+j1] = d_vfield_x[idx+j2]; 
                d_vfield0_y[idx+j1] = d_vfield_y[idx+j2];
            }

            // //Saves approx 1ms
            // std::copy(d_vfield_x + j2, d_vfield_x + j2 + Size, d_vfield0_x + j1);
            // std::copy(d_vfield_y + j2, d_vfield_y + j2 + Size, d_vfield0_y + j1);
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
            double xval = 0.5 * idx;
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
            // cout << "fftw second: " << chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - t1).count() <<'\n';
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

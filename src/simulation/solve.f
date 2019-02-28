#include "simulation.ih"
#include <omp.h>

// voor de duidelijkheid list ik de approximate regelnummers uit de
// solve.cc file

template <int Size>
void Simulation<Size>::solve()
{
    int gridsize_sq = Size * Size;

    // cout << accumulate(d_vfield0_x.begin(), d_vfield0_x.end(), 0.0) << "\n";

    // solve.cc: 9
    // #pragma omp parallel
    {
        #pragma omp for
        for (int idx = 0; idx < gridsize_sq; ++idx)
        {
            d_vfield_x[idx] += d_timestep * d_vfield0_x[idx];
            d_vfield0_x[idx] = d_vfield_x[idx];

            d_vfield_y[idx] += d_timestep * d_vfield0_y[idx];
            d_vfield0_y[idx] = d_vfield_y[idx];
        }

        // solve.cc 12
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            // deze zat in de for, eruitgehaald.
            double yval = (0.5 / Size) + jdx * (1.0 / Size);

            int j1 = Size * jdx;
            for (int idx = 0; idx < Size; ++idx)
            {
                size_t pos = idx + j1;

                double xval = (0.5 / Size) + idx * (1.0 / Size);
                double x0 = Size * (xval - d_timestep * d_vfield0_x[pos]) - 0.5f;
                double y0 = Size * (yval - d_timestep * d_vfield0_y[pos]) - 0.5f;
                int i0 = clamp(x0);
                double s = x0 - i0;
                i0 = (i0 + Size) % Size; 
                int i1 = (i0 + 1) % Size;
                int j0 = clamp(y0);
                double t = y0 - j0;
                j0 = (j0 + Size) % Size; 
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
            }
        }

        // solve.cc 27
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            size_t j2 = Size * jdx;
            size_t j1 = (Size + 2) * jdx;
            for (int idx = 0; idx < Size; ++idx)
            {
                d_vfield0_x[idx + j1]
                    = d_vfield_x[idx + j2];
                d_vfield0_y[idx + j1]
                    = d_vfield_y[idx + j2];
            }
        }

        // solve.cc 31
        // this is some hacky shit I dont even
        #pragma omp sections
        {
            {rfftwnd_one_real_to_complex
            (
                d_plan_rtoc_1,
                d_vfield0_x.data(),
                reinterpret_cast<fftw_complex *>(d_vfield0_x.data())
            );}
            #pragma omp section
            // solve.cc 32
            {rfftwnd_one_real_to_complex
            (
                d_plan_rtoc_2,
                d_vfield0_y.data(),
                reinterpret_cast<fftw_complex *>(d_vfield0_y.data())
            );}
        }
        #pragma omp barrier
        // solve.cc 34
        #pragma omp for
        for (int idx = 0; idx <= Size; idx += 2)
        {
            double xval = 0.5 * idx;
            double x2 = xval * xval;
            for (int jdx = 0; jdx < Size; ++jdx)
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

                size_t pos0 = idx + (Size + 2) * jdx;
                size_t pos1 = idx + 1 + (Size + 2) * jdx;
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

        // solve.cc 53
        // Sanity restored

        #pragma omp sections
        {
            {rfftwnd_one_complex_to_real
            (
                d_plan_ctor_1,
                reinterpret_cast<fftw_complex *>(d_vfield0_x.data()),
                d_vfield0_x.data()
            );}
            #pragma omp section
            {rfftwnd_one_complex_to_real
            (
                d_plan_ctor_2,
                reinterpret_cast<fftw_complex *>(d_vfield0_y.data()),
                d_vfield0_y.data()
            );}
        }

        #pragma omp barrier

        //solve.cc 56
        double f = 1.0 / (gridsize_sq);
        #pragma omp for
        for (int jdx = 0; jdx < Size; ++jdx)
        {
            size_t y1 = Size * jdx;
            size_t y2 = (Size + 2) * jdx;
            for (int idx = 0; idx < Size; ++idx)
            {
                d_vfield_x[idx + y1] = f * d_vfield0_x[idx + y2];
                d_vfield_y[idx + y1] = f * d_vfield0_y[idx + y2];
            }
        }
    }
}
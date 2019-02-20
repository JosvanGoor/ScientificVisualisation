#include "simulation.ih"

// voor de duidelijkheid list ik de approximate regelnummers uit de
// solve.cc file

void Simulation::solve()
{
    int gridsize_sq = d_gridsize * d_gridsize;

    // solve.cc: 9
    for (int idx = 0; idx < gridsize_sq; ++idx)
    {
        d_vfield0_x[idx] *= d_timestep;
        d_vfield0_y[idx] *= d_timestep;
    }

    // solve.cc 10
    d_vfield_x = d_vfield0_x;
    d_vfield0_y = d_vfield0_y;

    // solve.cc 12
    for (int idx = 0; idx < d_gridsize; ++idx)
    {
        // deze zat in de for, eruitgehaald.
        double xval = (0.5 / d_gridsize) + idx * (1.0 / d_gridsize);

        for (int jdx = 0; jdx < d_gridsize; ++jdx)
        {
            size_t pos = idx + d_gridsize * jdx;

            double yval = (0.5 / d_gridsize) + jdx * (1.0 / d_gridsize);
            double x0 = d_gridsize * (xval - d_timestep * d_vfield_x[pos]) - 0.5f;
            double y0 = d_gridsize * (yval - d_timestep * d_vfield_x[pos]) - 0.5f;
            int i0 = clamp(x0);
            double s = x0 - i0;
            i0 = (d_gridsize + (i0 % d_gridsize)) % d_gridsize; //kan met 1 modulo minder?
            int i1 = (i0 + 1) % d_gridsize;
            int j0 = clamp(y0);
            double t = y0 - j0;
            j0 = (d_gridsize + (j0 % d_gridsize)) % d_gridsize; //kan met 1 modulo minder?
            int j1 = (j0 + 1) % d_gridsize;

            size_t pos00 = i0 + d_gridsize * j0;
            size_t pos01 = i0 + d_gridsize * j1;
            size_t pos10 = i1 + d_gridsize * j0;
            size_t pos11 = i1 + d_gridsize * j1;
            // solve.cc 23
            d_vfield_x[pos] = (1 - s) * ((1 - t) * d_vfield0_x[pos00] + t * d_vfield0_x[pos01])
                + s * ((1 - t) * d_vfield0_x[pos10] + t * d_vfield0_x[pos11]);
            // solve.cc 24
            d_vfield_y[pos] = (1 - s) * ((1 - t) * d_vfield0_y[pos00] + t * d_vfield0_y[pos01])
                + s * ((1 - t) * d_vfield0_y[pos10] + t * d_vfield0_y[pos11]);
        }
    }

    // solve.cc 27
    for (int idx = 0; idx < d_gridsize; ++idx)
    {
        for (int jdx = 0; jdx < d_gridsize; ++jdx)
        {
            d_vfield0_x[idx + (d_gridsize + 2) * jdx]
                = d_vfield_x[idx + d_gridsize * jdx];
            d_vfield0_y[idx + (d_gridsize + 2) * jdx]
                = d_vfield_y[idx + d_gridsize * jdx];
        }
    }

    // solve.cc 31
    // this is some hacky shit I dont even
    rfftwnd_one_real_to_complex
    (
        d_plan_rtoc,
        d_vfield0_x.data(),
        reinterpret_cast<fftw_complex *>(d_vfield0_x.data())
    );

    // solve.cc 32
    rfftwnd_one_real_to_complex
    (
        d_plan_rtoc,
        d_vfield0_y.data(),
        reinterpret_cast<fftw_complex *>(d_vfield0_y.data())
    );
    
    // solve.cc 34
    for (int idx = 0; idx < d_gridsize; idx += 2)
    {
        double xval = 0.5 * idx;
        for (int jdx = 0; jdx < d_gridsize; ++jdx)
        {
            double yval = jdx <= (d_gridsize / 2) ? jdx : (jdx - d_gridsize);
            double r = xval * xval + yval * yval;
            
            if (r == 0.0)
                continue;

            double f = exp(-r * d_timestep * d_viscosity);

            double U[2]; //there obviously is no better way of doing this.
            double V[2];

            size_t pos0 = idx + (d_gridsize + 2) * jdx;
            size_t pos1 = idx + 1 + (d_gridsize + 2) * jdx;
            U[0] = d_vfield0_x[pos0];
            U[1] = d_vfield0_x[pos1];
            V[0] = d_vfield0_y[pos0];
            V[1] = d_vfield0_y[pos1];

            d_vfield0_x[pos0] = f * ((1 - xval * xval / r) * U[0] - xval * yval / r * V[0]);
            d_vfield0_x[pos1] = f * ((1 - xval * xval / r) * U[1] - xval * yval / r * V[1]);
            d_vfield0_y[pos0] = f * (-yval * xval / r * U[0] + (1 - yval * yval / r) * V[0]);
            d_vfield0_y[pos1] = f * (-yval * xval / r * U[1] + (1 - yval * yval / r) * V[1]);
        }
    }

    // solve.cc 53
    // Sanity restored
    rfftwnd_one_complex_to_real
    (
        d_plan_ctor,
        reinterpret_cast<fftw_complex *>(d_vfield0_x.data()),
        d_vfield0_x.data()
    );

    rfftwnd_one_complex_to_real
    (
        d_plan_ctor,
        reinterpret_cast<fftw_complex *>(d_vfield0_y.data()),
        d_vfield0_y.data()
    );

    //solve.cc 56
    double f = 1.0 / (gridsize_sq);
    for (int idx = 0; idx < d_gridsize; ++idx)
    {
        for (int jdx = 0; jdx < d_gridsize; ++jdx)
        {
            d_vfield_x[idx + d_gridsize + jdx]
                = f * d_vfield0_x[idx + (d_gridsize + 2) * jdx];
            d_vfield_y[idx + d_gridsize + jdx]
                = f * d_vfield0_y[idx + (d_gridsize + 2) * jdx];
        }
    }
}
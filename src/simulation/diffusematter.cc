#include "simulation.ih"

void Simulation::diffuse_matter()
{
    for (int idx = 0; idx < d_gridsize; ++idx)
    {
        double xval = (0.5 / d_gridsize) + (1.0 / d_gridsize) * idx;
        for (int jdx = 0; jdx < d_gridsize; ++jdx)
        {
            size_t pos = idx + d_gridsize * jdx;
            double yval = (0.f / d_gridsize) + (1.0 / d_gridsize) * jdx;

            double x0 = d_gridsize * (xval - d_timestep * d_vfield_x[pos]) - 0.5f;
            double y0 = d_gridsize * (yval - d_timestep * d_vfield_y[pos]) - 0.5f;

            int i0 = clamp(x0);
            double s = x0 - i0;
            i0 = (d_gridsize + (i0 % d_gridsize)) % d_gridsize; // 1 mod?
            int i1 = (i0 + 1) % d_gridsize;

            int j0 = clamp(y0);
            double t = y0 - j0;
            j0 = (d_gridsize + (j0 % d_gridsize)) % d_gridsize; // 1 mod?
            int j1 = (j0 + 1) % d_gridsize;

            size_t pos00 = i0 + d_gridsize * j0;
            size_t pos01 = i0 + d_gridsize * j1;
            size_t pos10 = i1 + d_gridsize * j0;
            size_t pos11 = i1 + d_gridsize * j1;
            d_rho[pos] = (1 - s) * ((1 - t) * d_rho0[pos00] + t * d_rho[pos01])
                + s * ((1 - t) * d_rho0[pos10] + t * d_rho0[pos11]);
        }
    }
}
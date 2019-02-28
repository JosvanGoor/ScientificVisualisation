#include "simulation.ih"

template <int Size>
void Simulation<Size>::diffuse_matter()
{
    #pragma omp for
    for (int jdx = 0; jdx < Size; ++jdx)
    {
        double yval = (0.5 / Size) + (1.0 / Size) * jdx;
        size_t offset = Size * jdx;
        for (int idx = 0; idx < Size; ++idx)
        {
            double xval = (0.5 / Size) + (1.0 / Size) * idx;
            size_t pos = idx + offset;

            double x0 = Size * (xval - d_timestep * d_vfield_x[pos]) - 0.5;
            double y0 = Size * (yval - d_timestep * d_vfield_y[pos]) - 0.5;

            int i0 = clamp(x0);
            double s = x0 - i0;
            i0 %= Size;
            int i1 = (i0 + 1) % Size;

            int j0 = clamp(y0);
            double t = y0 - j0;
            j0 %= Size;
            int j1 = (j0 + 1) % Size;

            size_t pos00 = i0 + Size * j0;
            size_t pos01 = i0 + Size * j1;
            size_t pos10 = i1 + Size * j0;
            size_t pos11 = i1 + Size * j1;
            d_rho[pos] = (1 - s) * ((1 - t) * d_rho0[pos00] + t * d_rho[pos01])
                + s * ((1 - t) * d_rho0[pos10] + t * d_rho0[pos11]);
        }
    }
}
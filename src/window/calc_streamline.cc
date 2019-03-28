#include "window.ih"

void Window::calc_streamline(size_t x, size_t y, size_t z)
{
    size_t curX = x;
    size_t curY = y;
    size_t newX, newY;

    double square = 1.0 / d_simulation.gridsize();

    for (size_t idx = z; idx != d_simulation.gridsize(); ++idx)
    {
        stream_lines.push_back(curX * square);
        stream_lines.push_back(curY * square);
        stream_lines.push_back(z * square);

        newX = curX + d_simulation.gridsize() - d_simulation.gridsize() * (d_simulation.timestep() * d_simulation.history_x()[idx][curX + curY * d_simulation.gridsize()]);
        newY = curY + d_simulation.gridsize() - d_simulation.gridsize() * (d_simulation.timestep() * d_simulation.history_y()[idx][curX + curY * d_simulation.gridsize()]);

        curX = newX % d_simulation.gridsize();
        curY = newY % d_simulation.gridsize();
    }
}
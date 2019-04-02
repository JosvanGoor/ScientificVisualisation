#include "window.ih"

void Window::calc_streamline(size_t x, size_t y, size_t z)
{
    double curX = x;
    double curY = y;

    double square = 1.0 / d_simulation.gridsize();

    for (size_t idx = z; idx != d_simulation.gridsize(); ++idx)
    {
        stream_lines.push_back(curX * square);
        stream_lines.push_back(curY * square);
        stream_lines.push_back(idx * square);

        double posX = curX + d_simulation.gridsize() * (d_simulation.timestep() * d_simulation.history_x()[idx][int(curX + curY * d_simulation.gridsize() + 0.5)]);
        double posY = curY + d_simulation.gridsize() * (d_simulation.timestep() * d_simulation.history_y()[idx][int(curX + curY * d_simulation.gridsize() + 0.5)]);

        curX = posX >= 0.0 ? posX : -(1 - posX);
        curX += d_simulation.gridsize();
        
        curY = posY >= 0.0 ? posY : -(1 - posY);
        curY += d_simulation.gridsize();

        while (curY >= d_simulation.gridsize())
            curY -= d_simulation.gridsize();

        while (curX >= d_simulation.gridsize())
            curX -= d_simulation.gridsize();
    }
}
#include "window.ih"

/*  Bilinear interpolation where p00 is scalar value at top left of unit square,
    p01 top right, p10 bottom left and p11 bottom right*/
double interpolate(double x, double y, double p00, double p01, double p10, double p11)
{
    if (x > 1 || x < 0 || y > 1 || y < 0)
        throw "x and y should be in range [0,1]";

    return p00 * (1 - x) * (1 - y) + p10 * x * (1 - y) + p01 * (1 - x) * y + p11 * x * y;
}


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

        double velX00 = d_simulation.history_x()[idx][int(curX) + int(curY) * d_simulation.gridsize()];
        double velX01 = d_simulation.history_x()[idx][int(curX) + 1 + int(curY) * d_simulation.gridsize()];
        double velX10 = d_simulation.history_x()[idx][int(curX) + (int(curY) + 1) * d_simulation.gridsize()];
        double velX11 = d_simulation.history_x()[idx][int(curX) + 1 + (int(curY) + 1) * d_simulation.gridsize()];
        double velY00 = d_simulation.history_y()[idx][int(curX) + int(curY) * d_simulation.gridsize()];
        double velY01 = d_simulation.history_y()[idx][int(curX) + 1 + int(curY) * d_simulation.gridsize()];
        double velY10 = d_simulation.history_y()[idx][int(curX) + (int(curY) + 1) * d_simulation.gridsize()];
        double velY11 = d_simulation.history_y()[idx][int(curX) + 1 + (int(curY) + 1) * d_simulation.gridsize()];

        double posX = curX + d_simulation.gridsize() * (d_simulation.timestep() * interpolate(curX - int(curX), curY - int(curY), velX00, velX01, velX10, velX11));
        double posY = curY + d_simulation.gridsize() * (d_simulation.timestep() * interpolate(curX - int(curX), curY - int(curY), velY00, velY01, velY10, velY11));

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
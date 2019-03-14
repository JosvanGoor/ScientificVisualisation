template <typename T> 
void Window::divergence(T velX, T velY)
{
    size_t row2, col2;
    #pragma omp for
    for (size_t row = 0; row < d_simulation.gridsize(); ++row)
    {
        row2 = (row + 1) % d_simulation.gridsize();
        for (size_t col = 0; col != d_simulation.gridsize(); ++col)
        {
            col2 = (col + 1) % d_simulation.gridsize();
            store[col + row * d_simulation.gridsize()] = velX[col + row2 * d_simulation.gridsize()] - velX[col + row * d_simulation.gridsize()]
                                                            + velY[col2 + row * d_simulation.gridsize()] - velY[col + row * d_simulation.gridsize()];
        }
    }
}
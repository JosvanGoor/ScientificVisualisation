#include "window.ih"

void Window::calc_lines(double iso)
{
    double size = 1.0 / d_simulation.gridsize();
    vector<double> &rho = d_simulation.rho();

    #pragma omp for
    for (size_t jdx = 0; jdx < d_simulation.gridsize() - 1; ++jdx)
    {
        size_t offset = jdx * d_simulation.gridsize();
        
        for (size_t idx = 0; idx != d_simulation.gridsize() - 1; ++idx)
        {
            size_t index = idx + offset;
            size_t type = 8 *   (rho[index] > iso) 
                        + 4 *   (rho[index + 1] > iso)
                        + 2 *   (rho[index + d_simulation.gridsize() + 1] > iso )
                        +       (rho[index + d_simulation.gridsize()] > iso );

            switch (type)
            {
                case 1:
                case 14:       
                    break;
                
                case 2:
                case 13:       
                    break;
                
                case 3:
                case 12:       
                    break;
                
                case 4:
                case 11:       
                    break;
                
                case 5:
                case 10:       
                    break;
                
                case 6:
                case 9:       
                    break;
                
                case 7:
                case 8:       
                    break;

                default:
                    break;
            }
        }
    }
    
}
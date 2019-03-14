#include "window.ih"

double interpolate(double val, double min_val, double max_val)
{
    return (val - min_val) / (max_val - min_val); 
}

void Window::calc_lines(double iso)
{
    double size = 1.0 / d_simulation.gridsize();
    vector<double> &rho = d_simulation.rho();
    double x1, y1, x2, y2;

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
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso,rho[index], rho[index + d_simulation.gridsize()])) ;
                    y2 = (jdx + 1) * size;

                    break;
                
                case 14:       
                    break;
                
                case 2:     
                    break;

                case 13:       
                    break;
                
                case 3:     
                    break;

                case 12:       
                    break;
                
                case 4:     
                    break;

                case 11:       
                    break;
                
                case 5:     
                    break;

                case 10:       
                    break;
                
                case 6:     
                    break;

                case 9:       
                    break;
                
                case 7:     
                    break;

                case 8:       
                    break;

                default:
                    break;
            }
        }
    }
    
}
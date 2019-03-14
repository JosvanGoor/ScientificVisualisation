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
                case 1:    //bottom left above iso
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso,rho[index], rho[index + d_simulation.gridsize()])) ;
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + 1 - interpolate(iso,rho[index + d_simulation.gridsize() + 1] ,rho[index + d_simulation.gridsize()]));
                    break;
                
                case 14:   //bottom left below iso
                    x1 = idx * size;
                    y1 = size * (jdx + 1 - interpolate(iso,rho[index + d_simulation.gridsize()],rho[index])) ;
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 2:     //bottom right above iso
                    x1 = (idx + 1) * size;
                    y1 = size * (jdx + interpolate(iso,rho[index + 1], rho[index + d_simulation.gridsize() + 1])) ;
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;

                case 13:   //bottom right below iso
                    x1 = (idx + 1) * size;
                    y1 = size * (jdx + 1 - interpolate(iso,rho[index + 1], rho[index + d_simulation.gridsize() + 1])) ;
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + 1 - interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 3:    //bottom 2 above iso
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;

                case 12:  //bottom 2 below iso
                    x1 = idx * size;
                    y1 = size * (jdx + 1 - interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + 1 - interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 4:  //top right above iso
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + 1 - interpolate(iso, rho[index + d_simulation.gridsize() + 1], rho[index + 1]));
                    break;

                case 11: //top right below iso
                    x1 = size * (idx + 1 - interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx +interpolate(iso, rho[index + d_simulation.gridsize() + 1], rho[index + 1]));
                    break;
                
                case 5:     
                    break;

                case 10:       
                    break;
                
                case 6:   
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    x2 = size * (idx + interpolate(iso, rho[index+ d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    y2 = (jdx + 1) * size;
                    break;

                case 9:       
                    x1 = size * (idx + 1 - interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    x2 = size * (idx + 1 - interpolate(iso, rho[index+ d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    y2 = (jdx + 1) * size;
                    break;
                
                case 7:     
                    x1 = size * idx;
 
                    y2 = size * jdx;
                    break;

                case 8:       
                    break;

                default:
                    break;
            }
        }
    }
    
}
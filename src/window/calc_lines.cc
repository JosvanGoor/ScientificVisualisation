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
                    //left
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //bottom
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 14:   //bottom left below iso
                    //left
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //bottom
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 2:     //bottom right above iso
                    //right
                    x1 = (idx + 1) * size;
                    y1 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    //bottom
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;

                case 13:   //bottom right below iso
                    //right
                    x1 = (idx + 1) * size;
                    y1 = size * (jdx + interpolate(iso, rho[index+1], rho[index + d_simulation.gridsize()+1]));
                    //bottom
                    y2 = (jdx + 1) * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 3:    //bottom 2 above iso
                    //left
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //right
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;

                case 12:  //bottom 2 below iso
                    //left
                    x1 = idx * size;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //right
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 4:  //top right above iso
                    //top
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    //right
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;

                case 11: //top right below iso
                    //top
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    //right
                    x2 = (idx + 1) * size;
                    y2 = size * (jdx + interpolate(iso, rho[index + 1], rho[index + d_simulation.gridsize() + 1]));
                    break;
                
                case 5:     
                    break;

                case 10:       
                    break;
                
                case 6:  //right 2 are above iso
                    //top
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    //bottom
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    y2 = (jdx + 1) * size;
                    break;

                case 9:  //left 2 are above iso
                    x1 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    y1 = jdx * size;
                    x2 = size * (idx + interpolate(iso, rho[index + d_simulation.gridsize()], rho[index + d_simulation.gridsize() + 1]));
                    y2 = (jdx + 1) * size;
                    break;
                
                case 7:  //top left below iso
                    //left
                    x1 = size * idx;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //top
                    y2 = size * jdx;
                    x2 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    break;

                case 8:  
                    //left     
                    x1 = size * idx;
                    y1 = size * (jdx + interpolate(iso, rho[index], rho[index + d_simulation.gridsize()]));
                    //top
                    y2 = size * jdx;
                    x2 = size * (idx + interpolate(iso, rho[index], rho[index + 1]));
                    break;

                default:
                    break;
            }

                
            if (type != 0 && type != 15 && type != 5 && type != 10)
            {
                #pragma omp critical
                {
                    if(x1 < 0.001)
                        cout << type << ", " << x1 << '\n';
                    if(x2 < 0.001)
                        cout << "x2: " << type << ", " << x2 << '\n';
                    if(x1 > 0.999)
                        cout << type << ", " << x1 << '\n';
                    if(x2 > 0.999)
                        cout << "x2: " << type << ", " << x2 << '\n';

                    if(abs(x2 - x1) > 2 * size)
                        cout << type<< ", " << idx << ", " << x1 << ' ' << x2 << '\n';
                    // cout << x1 << ", " << y1 << ", " << x2 << ", " << y2 << '\n';
                    lines.push_back(x1);
                    lines.push_back(y1);
                    lines.push_back(x2);
                    lines.push_back(y2);
                }
            }
        }
    }
    
}
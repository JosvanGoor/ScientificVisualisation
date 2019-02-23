#include "window.ih"

void Window::paint_smoke()
{
    double wn = d_width / static_cast<double>(d_simulation.gridsize() + 1);
    double hn = d_height / static_cast<double>(d_simulation.gridsize() + 1);

    vector<float> triangles;
    vector<float> colors;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
    //     glBegin(GL_TRIANGLE_STRIP);

        int idx = 0;
        float px = wn + idx * wn; // think about this...
        float py = hn + jdx * hn;
        int index = jdx * d_simulation.gridsize() + idx;

        Color col{d_simulation.rho()[index], d_simulation.rho()[index], d_simulation.rho()[index]};
        colors.insert(colors.end(), col.begin(), col.end());
        triangles.push_back(px);
        triangles.push_back(py);

        for (; idx < d_simulation.gridsize(); ++idx)
        {
            px = wn + idx * wn;
            py = hn + (jdx + 1) * hn;
            index = ((jdx + 1) * d_simulation.gridsize()) + idx;
            col = colormap(d_simulation.rho()[index]);
            colors.insert(colors.end(), col.begin(), col.end());
            triangles.push_back(px);
            triangles.push_back(py);
    
            px = wn + (idx + 1) * wn;
            py = hn + jdx * hn;
            index = (jdx * d_simulation.gridsize()) + (idx + 1);
            col = colormap(d_simulation.rho()[index]);
            colors.insert(colors.end(), col.begin(), col.end());
            triangles.push_back(px);
            triangles.push_back(py);
        }

        px = wn + (d_simulation.gridsize() - 1) * wn;
        py = hn + (jdx + 1) * hn;
        index = ((jdx + 1) * d_simulation.gridsize()) + (d_simulation.gridsize() - 1);
        col = colormap(d_simulation.rho()[index]);
        colors.insert(colors.end(), col.begin(), col.end());
        triangles.push_back(px);
        triangles.push_back(py);

    }
}
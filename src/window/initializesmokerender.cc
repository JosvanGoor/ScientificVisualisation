#include "window.ih"

void Window::initialize_smoke_render()
{
    d_rendermodel = make_unique<SmokeRenderModel>();

    double wn = d_width / static_cast<double>(d_simulation.gridsize());
    double hn = d_height / static_cast<double>(d_simulation.gridsize());

    vector<float> triangles;

    for (int jdx = 0; jdx < (d_simulation.gridsize() - 1); ++jdx)
    {
        int idx = 0;
        float px = idx * wn; // think about this...
        float py = jdx * hn;

        triangles.push_back(px);
        triangles.push_back(py);

        for (; idx < (d_simulation.gridsize() - 1); ++idx)
        {
            px = idx * wn;
            py = (jdx + 1) * hn;
            triangles.push_back(px);
            triangles.push_back(py);

            px = (idx + 1) * wn;
            py = jdx * hn;
            triangles.push_back(px);
            triangles.push_back(py);
        }

        px = (d_simulation.gridsize() - 1) * wn;
        py = (jdx + 1) * hn;
        triangles.push_back(px);
        triangles.push_back(py);
    }

    d_rendermodel->set_vertex_data(triangles);
    d_rendermodel->set_drawcount(d_simulation.gridsize());
}
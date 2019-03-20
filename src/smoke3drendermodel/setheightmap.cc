#include "smoke3drendermodel.ih"

#include <iostream> 

void Smoke3dRenderModel::set_heightmap(vector<float> const &height, float min, float max)
{
    // no range check....
    for (size_t idx = 0; idx < height.size(); ++idx)
    {
        d_triangles[idx * 3 + 2] = height[idx]; // range checks
    }

    cout << __PRETTY_FUNCTION__ << "\n";
    cout << "sizeof height: " << height.size() << "\n";
    cout << "sizeof  tri's: " << d_triangles.size() << "\n";

    vector<float> normals;
    size_t pt_idx = 0;
    for (int jdx = 0; jdx < d_gridsize; ++jdx)
    {
        for (int idx = 0; idx < ((d_gridsize - 1) * 2); ++idx)
        {
            vec3 u;
            vec3 v;
            
            size_t offset = pt_idx * 3;

            if (pt_idx % 2 == 0)
            {
                u = 
                {
                    d_triangles[offset + 0] - d_triangles[offset + 3],
                    d_triangles[offset + 1] - d_triangles[offset + 4],
                    d_triangles[offset + 2] - d_triangles[offset + 5]
                };

                v = 
                {
                    d_triangles[offset + 6] - d_triangles[offset + 3],
                    d_triangles[offset + 7] - d_triangles[offset + 4],
                    d_triangles[offset + 8] - d_triangles[offset + 5]
                };
            }
            else
            {
                u = 
                {
                    d_triangles[offset + 3] - d_triangles[offset + 0],
                    d_triangles[offset + 4] - d_triangles[offset + 1],
                    d_triangles[offset + 5] - d_triangles[offset + 2]
                };

                v = 
                {
                    d_triangles[offset + 6] - d_triangles[offset + 0],
                    d_triangles[offset + 7] - d_triangles[offset + 1],
                    d_triangles[offset + 8] - d_triangles[offset + 2]
                };
            }

            vec3 n = normalize(cross(u, v));
            
            normals.insert(normals.end(),
            {
                n.x, n.y, n.z,
                n.x, n.y, n.z,
                n.x, n.y, n.z
            });

            ++pt_idx;
        }

        pt_idx += 2;
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, d_triangles.size() * sizeof(float), d_triangles.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_hmin = min;
    d_hmax = max;
}
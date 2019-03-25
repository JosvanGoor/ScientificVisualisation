#include "smoke3drendermodel.ih"

#include <iostream> 

void Smoke3dRenderModel::set_heightmap(vector<float> const &height, float min, float max)
{

    for (size_t row = 0; row < (d_gridsize - 1); ++row)
    {
        for (size_t col = 0; col < (d_gridsize - 1); ++col)
        {
            size_t offset = (row * (d_gridsize - 1) + col) * 18;
            
            d_triangles[offset + 2] = height[row * d_gridsize + col];
            d_triangles[offset + 5] = height[(row + 1) * d_gridsize + col];
            d_triangles[offset + 8] = height[row * d_gridsize + col + 1];
            d_triangles[offset + 11] = height[row * d_gridsize + col + 1];
            d_triangles[offset + 14] = height[(row + 1) * d_gridsize + col];
            d_triangles[offset + 17] = height[(row + 1) * d_gridsize + col + 1];
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_triangles.size(), d_triangles.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vector<float> normals;
    for (size_t idx = 0; idx < d_triangles.size() / 3; ++idx)
    {
        normals.insert(normals.end(),
        {
            0.0f, 0.0f, 1.0f
        });
    }
    // size_t pt_idx = 0;
    // for (int jdx = 0; jdx < (d_gridsize - 1); ++jdx)
    // {
    //     for (int idx = 0; idx < ((d_gridsize - 1) * 2); ++idx)
    //     {
    //         vec3 u;
    //         vec3 v;
            
    //         size_t offset = pt_idx * 3;

    //         if (pt_idx % 2 == 0)
    //         {
    //             u = 
    //             {
    //                 d_triangles[offset + 0] - d_triangles[offset + 3],
    //                 d_triangles[offset + 1] - d_triangles[offset + 4],
    //                 d_triangles[offset + 2] - d_triangles[offset + 5]
    //             };

    //             v = 
    //             {
    //                 d_triangles[offset + 6] - d_triangles[offset + 3],
    //                 d_triangles[offset + 7] - d_triangles[offset + 4],
    //                 d_triangles[offset + 8] - d_triangles[offset + 5]
    //             };
    //         }
    //         else
    //         {
    //             u = 
    //             {
    //                 d_triangles[offset + 3] - d_triangles[offset + 0],
    //                 d_triangles[offset + 4] - d_triangles[offset + 1],
    //                 d_triangles[offset + 5] - d_triangles[offset + 2]
    //             };

    //             v = 
    //             {
    //                 d_triangles[offset + 6] - d_triangles[offset + 0],
    //                 d_triangles[offset + 7] - d_triangles[offset + 1],
    //                 d_triangles[offset + 8] - d_triangles[offset + 2]
    //             };
    //         }

    //         vec3 n = normalize(cross(u, v));
            
    //         normals.insert(normals.end(),
    //         {
    //             n.x, n.y, n.z,
    //             n.x, n.y, n.z,
    //             n.x, n.y, n.z
    //         });

    //         ++pt_idx;
    //     }

    //     pt_idx += 2;
    // }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, d_triangles.size() * sizeof(float), d_triangles.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_hmin = min;
    d_hmax = max;
}
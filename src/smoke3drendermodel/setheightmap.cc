#include "smoke3drendermodel.ih"

#include <functional>
#include <iostream> 

void Smoke3dRenderModel::set_heightmap(vector<float> const &height, float min, float max)
{

    auto map = std::bind(
        [](float val, float low, float high) -> float
        {
            float rval = std::max(std::min(val, high), low);
            return (rval - low) / (high - low);
        },
        std::placeholders::_1,
        min,
        max
    );

    for (size_t row = 0; row < (d_gridsize - 1); ++row)
    {
        for (size_t col = 0; col < (d_gridsize - 1); ++col)
        {
            size_t offset = (row * (d_gridsize - 1) + col) * 18;
            
            d_triangles[offset + 2] = map(height[row * d_gridsize + col]);
            d_triangles[offset + 5] = map(height[(row + 1) * d_gridsize + col]);
            d_triangles[offset + 8] = map(height[row * d_gridsize + col + 1]);
            d_triangles[offset + 11] = map(height[row * d_gridsize + col + 1]);
            d_triangles[offset + 14] = map(height[(row + 1) * d_gridsize + col]);
            d_triangles[offset + 17] = map(height[(row + 1) * d_gridsize + col + 1]);
        }
    }

    vector<float> normals;
    normals.reserve(d_triangles.size());
    for (size_t idx = 0; idx < d_triangles.size() / 9; ++idx)
    {
        size_t offset = 9 * idx;

        vec3 u = 
        {
            d_triangles[offset + 0] - d_triangles[offset + 3],
            d_triangles[offset + 1] - d_triangles[offset + 4],
            d_triangles[offset + 2] - d_triangles[offset + 5]
        };

        vec3 v = 
        {
            d_triangles[offset + 6] - d_triangles[offset + 3],
            d_triangles[offset + 7] - d_triangles[offset + 4],
            d_triangles[offset + 8] - d_triangles[offset + 5]
        };

        vec n = normalize(cross(u, v));
        normals.insert(normals.end(),
        {
            n.x, n.y, n.z,
            n.x, n.y, n.z,
            n.x, n.y, n.z
        });
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_triangles.size(), d_triangles.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    // glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    // glBufferData(GL_ARRAY_BUFFER, d_triangles.size() * sizeof(float), d_triangles.data(), GL_STREAM_DRAW);

    d_hmin = min;
    d_hmax = max;
}
#include "smoke3drendermodel.ih"

#include <functional>
#include <iostream> 

void Smoke3dRenderModel::set_heightmap(vector<float> const &height, float min, float max)
{

    auto map = std::bind(
        [](float val, float low, float high) -> float
        {
            float rval = std::max(val, low);
            // if rval >> high then we dont cut it off but quickly scale down
            // the peak by taking the cubic root. This prevents plateau forming
            rval = (rval - low) / (high - low);

            if (rval > 1.0)
                return std::cbrt(rval);
            return rval;


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

    size_t maxoffset = 0;
    auto offset = [&](int col, int row)
    {
        col = (col + d_gridsize) % (d_gridsize - 1);
        row = (row + d_gridsize) % (d_gridsize - 1);

        maxoffset = (18 * d_gridsize * row) + (18 * col) > maxoffset
            ? (18 * d_gridsize * row) + (18 * col)
            : maxoffset;

        return static_cast<size_t>
        (
            (18 * (d_gridsize - 1) * row) + (18 * col)
        );
    };

    vector<float> smooths;
    smooths.resize(normals.size());
    for (int row = 0; row < (d_gridsize - 1); ++row)
    {
        for (int col = 0; col < (d_gridsize - 1); ++col)
        {
            // sum the 6 connecting normals
            glm::vec3 smooth{0.0f};
            smooth += glm::vec3
            (
                normals[offset(col - 1, row) + 15],
                normals[offset(col - 1, row) + 16],
                normals[offset(col - 1, row) + 17]
            );

            smooth += glm::vec3
            (
                normals[offset(col, row) + 3],
                normals[offset(col, row) + 4],
                normals[offset(col, row) + 5]
            ) * 2.0f; // TIMES 2

            smooth += glm::vec3
            (
                normals[offset(col, row + 1) + 0],
                normals[offset(col, row + 1) + 1],
                normals[offset(col, row + 1) + 2]
            );

            smooth += glm::vec3
            (
                normals[offset(col - 1, row + 1) + 6],
                normals[offset(col - 1, row + 1) + 7],
                normals[offset(col - 1, row + 1) + 8]
            ) * 2.0f; // TIMES 2

            smooth = normalize(smooth);
            
            smooths[offset(col - 1, row) + 15] = smooth.x;
            smooths[offset(col - 1, row) + 16] = smooth.y;
            smooths[offset(col - 1, row) + 17] = smooth.z;
            
            smooths[offset(col, row) + 3] = smooth.x;
            smooths[offset(col, row) + 4] = smooth.y;
            smooths[offset(col, row) + 5] = smooth.z;

            smooths[offset(col, row) + 12] = smooth.x;
            smooths[offset(col, row) + 13] = smooth.y;
            smooths[offset(col, row) + 14] = smooth.z;

            smooths[offset(col, row + 1) + 0] = smooth.x;
            smooths[offset(col, row + 1) + 1] = smooth.y;
            smooths[offset(col, row + 1) + 2] = smooth.z;

            smooths[offset(col - 1, row + 1) + 6] = smooth.x;
            smooths[offset(col - 1, row + 1) + 7] = smooth.y;
            smooths[offset(col - 1, row + 1) + 8] = smooth.z;

            smooths[offset(col - 1, row + 1) + 9] = smooth.x;
            smooths[offset(col - 1, row + 1) + 10] = smooth.y;
            smooths[offset(col - 1, row + 1) + 11] = smooth.z;

            maxoffset = 0;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * d_triangles.size(), d_triangles.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, d_smoke_normals);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), smooths.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    d_hmin = min;
    d_hmax = max;
}
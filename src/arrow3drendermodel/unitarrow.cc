#include "arrow3drendermodel.ih"

namespace
{
    vector<glm::vec3> bottom_coordinates(size_t detail)
    {
        float angle_step = 360.0f / (detail);
        vector<glm::vec3> points;

        for (size_t idx = 0; idx < detail; ++idx)
        {
            points.push_back
            (
                glm::vec3{0.0f, 0.5 * sin(angle_step * idx), 0.5 * cos(angle_step * idx)}
            );
        }

        return points;
    }
}

vector<float> Arrow3dRenderModel::unit_arrow(size_t detail)
{
    d_drawcount = 0;
    vector<glm::vec3> points = bottom_coordinates(detail);
    vector<float> triangles;
    
    /* HEAD */
    for (size_t idx = 0; idx < (detail - 1); ++idx)
    {
        triangles.insert(triangles.end(),
        {
            points[idx + 1].x,
            points[idx + 1].y,
            points[idx + 1].z
        });

        triangles.insert(triangles.end(),
        {
            1.0f, 0.0f, 0.0f
        });

        triangles.insert(triangles.end(),
        {
            points[idx].x,
            points[idx].y,
            points[idx].z
        });
        d_drawcount += 3;
    }

    /* Bottom base */
    for (size_t idx = 0; idx < (detail - 1); ++idx)
    {
        triangles.insert(triangles.end(),
        {
            points[idx + 1].x,
            points[idx + 1].y,
            points[idx + 1].z
        });

        triangles.insert(triangles.end(),
        {
            0.0f, 0.0f, 0.0f
        });

        triangles.insert(triangles.end(),
        {
            points[idx].x,
            points[idx].y,
            points[idx].z
        });
        d_drawcount += 3;
    }

    /* Tail */
    const float foot_ratio = 0.35;
    for (size_t idx = 0; idx < (detail - 1); ++idx)
    {
        /* tri 1 */
        triangles.insert(triangles.end(),
        {
            points[idx].x,
            foot_ratio * points[idx].y,
            foot_ratio * points[idx].z,
        });

        triangles.insert(triangles.end(),
        {
            points[idx].x - 1.0f,
            foot_ratio * points[idx].y,
            foot_ratio * points[idx].z,
        });

        triangles.insert(triangles.end(),
        {
            points[idx + 1].x - 1.0f,
            foot_ratio * points[idx + 1].y,
            foot_ratio * points[idx + 1].z,
        });

        /* tri 2 */
        triangles.insert(triangles.end(),
        {
            points[idx].x,
            foot_ratio * points[idx].y,
            foot_ratio * points[idx].z,
        });

        triangles.insert(triangles.end(),
        {
            points[idx + 1].x - 1.0f,
            foot_ratio * points[idx + 1].y,
            foot_ratio * points[idx + 1].z,
        });

        triangles.insert(triangles.end(),
        {
            points[idx + 1].x,
            foot_ratio * points[idx + 1].y,
            foot_ratio * points[idx + 1].z,
        });

        d_drawcount += 6;
    }

    for (size_t idx = 0; idx < (detail - 1); ++idx)
    {
        triangles.insert(triangles.end(),
        {
            foot_ratio * points[idx + 1].x - 1.0f,
            foot_ratio * points[idx + 1].y,
            foot_ratio * points[idx + 1].z
        });

        triangles.insert(triangles.end(),
        {
            -1.0f, 0.0f, 0.0f
        });

        triangles.insert(triangles.end(),
        {
            foot_ratio * points[idx].x - 1.0f,
            foot_ratio * points[idx].y,
            foot_ratio * points[idx].z
        });
        d_drawcount += 3;
    }

    return triangles;
}
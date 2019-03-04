#include "arrow3drendermodel.ih"

namespace
{
    glm::vec3 surface_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        glm::vec3 U = p2 - p1;
        glm::vec3 V = p3 - p1;
        
        // return outward_normal(U * V, (p1 + p2 + p3) / 3.0f);
        return U * V;
    }

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

    void push_clockwise(vector<float> &vertices, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        glm::vec3 center = -((p1 + p2 + p3) / 3.0f);
        glm::vec3 normal = surface_normal(p1, p2, p3);

        // if (dot(normal, center) > 0.0f)
        // {
        //     vertices.insert(vertices.end(),
        //     {
        //         p1.x, p1.y, p1.z,
        //         p2.x, p2.y, p2.z,
        //         p3.x, p3.y, p3.z
        //     });
        //     return;
        // }

        // normal = surface_normal(p1, p3, p2);
        // if (dot(normal, center) > 0.0f)
        // {
        //     vertices.insert(vertices.end(),
        //     {
        //         p1.x, p1.y, p1.z,
        //         p3.x, p3.y, p3.z,
        //         p2.x, p2.y, p2.z
        //     });
        //     return;
        // }

        // normal = surface_normal(p3, p2, p1);
        // if (dot(normal, center) > 0.0f)
        // {
        //     vertices.insert(vertices.end(),
        //     {
        //         p3.x, p3.y, p3.z,
        //         p2.x, p2.y, p2.z,
        //         p1.x, p1.y, p1.z
        //     });
        //     return;
        // }

        vertices.insert(vertices.end(),
        {
            p2.x, p2.y, p2.z,
            p3.x, p3.y, p3.z,
            p1.x, p1.y, p1.z
        });
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
        push_clockwise
        (
            triangles,
            points[idx + 1],
            glm::vec3{1.0f, 0.0f, 0.0f},
            points[idx]
        );
        
        // triangles.insert(triangles.end(),
        // {
        //     points[idx + 1].x,
        //     points[idx + 1].y,
        //     points[idx + 1].z
        // });

        // triangles.insert(triangles.end(),
        // {
        //     1.0f, 0.0f, 0.0f
        // });

        // triangles.insert(triangles.end(),
        // {
        //     points[idx].x,
        //     points[idx].y,
        //     points[idx].z
        // });
        d_drawcount += 3;
    }

    /* Bottom base */
    for (size_t idx = 0; idx < (detail - 1); ++idx)
    {
        push_clockwise
        (
            triangles,
            points[idx + 1],
            glm::vec3{0.0f, 0.0f, 0.0f},
            points[idx]
        );

        // triangles.insert(triangles.end(),
        // {
        //     points[idx + 1].x,
        //     points[idx + 1].y,
        //     points[idx + 1].z
        // });

        // triangles.insert(triangles.end(),
        // {
        //     0.0f, 0.0f, 0.0f
        // });

        // triangles.insert(triangles.end(),
        // {
        //     points[idx].x,
        //     points[idx].y,
        //     points[idx].z
        // });
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
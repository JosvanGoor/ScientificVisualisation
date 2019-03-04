#include "arrow3drendermodel.ih"

namespace
{
    glm::vec3 outward_normal(glm::vec3 norm, glm::vec3 p1)
    {
        if (glm::dot(norm, p1) < 0.0)
            return -norm;
        return norm;
    }

    glm::vec3 surface_normal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
    {
        glm::vec3 U = p2 - p1;
        glm::vec3 V = p3 - p1;
        
        // return outward_normal(U * V, (p1 + p2 + p3) / 3.0f);
        return U * V;
    }
}

vector<float> Arrow3dRenderModel::unit_arrow_normals(vector<float> const &vertices)
{
    vector<float> normals;
    normals.reserve(vertices.size());

    for (size_t idx = 0; idx < vertices.size();)
    {
        glm::vec3 normal = surface_normal
        (
            glm::vec3{vertices[idx++], vertices[idx++], vertices[idx++]},
            glm::vec3{vertices[idx++], vertices[idx++], vertices[idx++]},
            glm::vec3{vertices[idx++], vertices[idx++], vertices[idx++]}
        );

        normals.insert(normals.end(),
        {
            normal.x, normal.y, normal.z,
            normal.x, normal.y, normal.z,
            normal.x, normal.y, normal.z
        });
    }

    return normals;
}
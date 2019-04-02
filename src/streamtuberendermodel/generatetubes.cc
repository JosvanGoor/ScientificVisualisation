#include "streamtuberendermodel.ih"

void StreamtubeRenderModel::generate_tubes(vector<float> const &lines, size_t nlayers)
{
    vector<float> vertices;

    const size_t nslices = 16;

    for (size_t idx = 0; idx < ((lines.size() / 3) - 1); ++idx)
    {
        const float radius = 0.5f;
        const float length = 7.0;

        glm::vec3 start = 
        {
            (lines[idx * 3 + 0] - 0.5) * 20,
            (lines[idx * 3 + 1] - 0.5) * 20,
            lines[idx * 3 + 2] * length
        };

        glm::vec3 end = 
        {
            (lines[idx * 3 + 3] - 0.5) * 20,
            (lines[idx * 3 + 4] - 0.5) * 20,
            lines[idx * 3 + 5] * length
        };

        for (size_t slice = 0; slice < nslices; ++slice)
        {

            float x0 = radius * cos((2 * pi() / nslices) * slice);
            float y0 = radius * sin((2 * pi() / nslices) * slice);
            float x1 = radius * cos((2 * pi() / nslices) * (slice + 1));
            float y1 = radius * sin((2 * pi() / nslices) * (slice + 1));

            vertices.insert(vertices.end(),
            {
                start.x + x0, start.y + y0, start.z,
                end.x + x0, end.y + y0, end.z,
                start.x + x1, start.y + y1, start.z,

                start.x + x1, start.y + y1, start.z,
                end.x + x0, end.y + y0, end.z,
                end.x + x1, end.y + y1, end.z
            });
        }
    }

    d_drawcount = vertices.size() / 3;
    glBindBuffer(GL_ARRAY_BUFFER, d_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
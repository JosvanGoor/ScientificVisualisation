#include "arrow3drendermodel.ih"

void Arrow3dRenderModel::update_scalar(vector<double> const &scalar, size_t gridsize)
{
    size_t numglyphs = d_arrow_dim * d_arrow_dim;
    vector<float> colors;
    colors.reserve(numglyphs);

    for (size_t row = 0; row < d_arrow_dim; ++row)
    {
        float approx_y = 1.0f / d_arrow_dim;
        approx_y = (0.5f * approx_y) + (approx_y * row);
        size_t ypos = static_cast<size_t>(approx_y * gridsize);
        
        for (size_t col = 0; col < d_arrow_dim; ++col)
        {
            float approx_x = 1.0f / d_arrow_dim;
            approx_x = (0.5f * approx_x) + (approx_x * col);
        
            size_t xpos = static_cast<size_t>(approx_x * gridsize);
            size_t index = (ypos * gridsize) + xpos;
        
            colors.push_back(scalar[index]);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, d_scalar_buffer);
    glBufferData(GL_ARRAY_BUFFER, bytesize(colors), colors.data(), GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#include "linerendermodel.ih"

vector<float> LineRenderModel::default_lines()
{
    vector<float> lines = 
    {
        -0.5f, -0.5f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        0.0f, 0.0f
    };

    return lines;
}
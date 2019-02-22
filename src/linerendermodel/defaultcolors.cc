#include "linerendermodel.ih"

vector<float> LineRenderModel::default_colors()
{
    vector<float> colors = 
    {
        1.0, 0.0, 0.0,
        1.0, 1.0, 1.0,

        0.0, 1.0, 0.0,
        1.0, 1.0, 1.0
    };

    return colors;
}
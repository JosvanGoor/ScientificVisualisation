#include "smokerendermodel.ih"

vector<float> SmokeRenderModel::default_colors()
{
    return vector<float>
    {
        1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0
    };
}
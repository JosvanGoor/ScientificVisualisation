#include "smokerendermodel.ih"

vector<float> SmokeRenderModel::default_tristrip()
{
    return vector<float>
    {
        100, 100, 400, 100,
        200, 400,
        200, 100,
        300, 400,
        300, 100,
        400, 400,
        400, 100
    };
}
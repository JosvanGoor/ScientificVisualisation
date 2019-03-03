#include "enums.ih"

string scalingmode_string(ScalingMode mode)
{
    switch(mode)
    {
        case ScalingMode::STATIC:
            return "ScalingMode::STATIC";
        
        case ScalingMode::DYNAMIC:
            return "ScalingMode::DYNAMIC";

        default:
            return "Unknown or Modval ColorMode";
    }
}
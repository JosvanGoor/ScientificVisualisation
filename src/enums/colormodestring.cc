#include "enums.ih"

string colormode_string(ColorMode mode)
{
    switch(mode)
    {
        case ColorMode::DENSITY:
            return "ColorMode::DENSITY";
        
        case ColorMode::FORCE:
            return "ColorMode::FORCE";

        case ColorMode::VELOCITY:
            return "ColorMode::VELOCITY";

        default:
            return "Unknown or Modval ColorMode";
    }
}
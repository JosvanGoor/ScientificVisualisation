#include "window.ih"

string colormapping_string(ColorMapping mapping)
{
    switch(mapping)
    {
        case ColorMapping::BLACKWHITE:
            return "ColorMapping::BLACKWHITE";
        
        case ColorMapping::RAINBOW:
            return "ColorMapping::RAINBOW";

        case ColorMapping::BANDS:
            return "ColorMapping::BANDS";

        case ColorMapping::SPACE:
            return "ColorMapping::SPACE";

        case ColorMapping::DUTCH:
            return "ColorMapping::DUTCH";

        default:
            return "UNKNOWN ColorMapping";
    }
}
#include "window.ih"

string drawmode_string(DrawMode mode)
{
    switch (mode)
    {
        case DrawMode::SMOKE:
            return "DrawMode::SMOKE";
        
        case DrawMode::VECTORS:
            return "DrawMode::VECTORS";

        default:
            return "UNKNOWN DrawMode";
    }
}
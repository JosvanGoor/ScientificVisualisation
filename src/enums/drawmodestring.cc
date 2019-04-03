#include "enums.ih"

string drawmode_string(DrawMode mode)
{
    switch (mode)
    {
        case DrawMode::SMOKE:
            return "DrawMode::SMOKE";
        
        case DrawMode::SMOKE3D:
            return "DrawMode::SMOKE3D";

        case DrawMode::STREAMTUBES:
            return "DrawMode::STREAMTUBES";

        case DrawMode::VECTORS:
            return "DrawMode::VECTORS";

        default:
            return "Unknown or Modval DrawMode";
    }
}
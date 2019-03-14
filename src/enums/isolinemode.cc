#include "enums.ih"

string isoline_string(IsolineMode mode)
{
    switch(mode)
    {
        case IsolineMode::OFF:
            return "IsolineMode::OFF";

        case IsolineMode::ISO2D:
            return "IsolineMode::ISO2D";
        
        default:
            return "Unknown or Modval IsolineMode";
    }
}
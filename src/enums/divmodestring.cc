#include "enums.ih"

string divmode_string(DivMode mode)
{
    switch (mode)
    {
        case DivMode::OFF:
            return "DivMode::OFF";
        
        case DivMode::ON:
            return "DrawMode::ON";

        default:
            return "Unknown or Modval DivMode";
    }
}
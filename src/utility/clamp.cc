#include "utility.ih"

int clamp(double val)
{
    return val >= 0.0
        ? static_cast<int>(val)
        : static_cast<int>(val + 1);
}

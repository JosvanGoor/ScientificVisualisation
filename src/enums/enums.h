#ifndef __INCLUDED_ENUMS_H
#define __INCLUDED_ENUMS_H

#include <string>

enum class DrawMode
{
    SMOKE,
    VECTORS,
    MODULO_VALUE,
    NONE,
};
std::string drawmode_string(DrawMode mode);

enum class ColorMapping
{
    BLACKWHITE,
    RAINBOW,
    BANDS,
    SPACE,
    DUTCH,
    MODULO_VALUE
};
std::string colormapping_string(ColorMapping mapping);

enum class ColorMode
{
    DENSITY,
    FORCE,
    VELOCITY,
    MODULO_VALUE
};
std::string colormode_string(ColorMode mode);


enum class ScalingMode
{
    STATIC,
    DYNAMIC,
    MODULO_VALUE
};
std::string scalingmode_string(ScalingMode mode);

#endif
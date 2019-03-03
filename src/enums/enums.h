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

/* Rotates all enum values between 0 and modulo_value */
template <typename Enum>
Enum rotate_enum(Enum val)
{
    return static_cast<Enum>
    (
        (static_cast<int>(val) + 1) % 
        static_cast<int>(Enum::MODULO_VALUE)
    );
}


#endif
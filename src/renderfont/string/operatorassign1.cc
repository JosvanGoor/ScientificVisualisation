#include "string.ih"

RenderFont::String &RenderFont::String::operator=(String &&other)
{
    swap(other);
    return *this;
}
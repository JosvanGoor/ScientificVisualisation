#include "window.ih"

#include <iostream>

std::string Window::print_shortcuts() const
{
    stringstream ss;
    ss << "Key:  Setting\n";
    ss << "  c:  Toggle color mapping [BLACKWHITE, RAINBOW, BANDS, SPACE, DUTCH]\n";
    ss << "  g:  Toggle glyph mode [NONE, GLYPH, ARROW]\n";
    ss << "  h:  Reprint this menu\n";
    ss << "  m:  Toggle color mode    [DENSITY, FORCE, VELOCITY]\n";
    ss << "  q:  Quit the program.\n";
    ss << "  r:  Toggle render mode   [SMOKE, VECTORS]\n";
    ss << "\n";
    return ss.str();
}
#include "window.ih"

#include <iostream>

std::string Window::print_shortcuts() const
{
    stringstream ss;
    ss << "Key:  Setting\n";
    ss << "  a:  Clear all streamline anchors\n";
    ss << "  c:  Toggle color mapping [BLACKWHITE, RAINBOW, BANDS, SPACE, DUTCH]\n";
    ss << "  d:  Toggle divergence rendering\n";
    ss << "  g:  Toggle glyph mode [NONE, GLYPH, ARROW3D]\n";
    ss << "  h:  Toggle this menu\n";
    ss << "  m:  Toggle color mode    [DENSITY, FORCE, VELOCITY]\n";
    ss << "  m:  (+shift) toggle heightmap mode\n";
    ss << "  q:  Quit the program.\n";
    ss << "  r:  Toggle render mode   [SMOKE, SMOKE3D, VECTORS]\n";
    ss << "\n";
    return ss.str();
}
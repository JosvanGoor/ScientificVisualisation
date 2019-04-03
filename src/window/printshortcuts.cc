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
    ss << "  i:  Toggle isolines\n";
    ss << "  i:  +shift: Toggle isoline colormode\n";
    ss << "  ,:  Decrease lower bound isoline range\n";
    ss << "  .:  Increase lower bound isoline range\n";
    ss << "  ,:  +shift: Decrease upper bound isoline range\n";
    ss << "  .:  +shift: Increase upper bound isoline range\n";
    ss << "  ,:  +ctrl:  Decrease amount of isolines\n";
    ss << "  .:  +ctrl:  Increase amount of isolines\n";
    ss << "  m:  Toggle color mode    [DENSITY, FORCE, VELOCITY]\n";
    ss << "  m:  +shift: Toggle heightmap mode\n";
    ss << "  s:  toggle auto scaling\n";
    ss << "  -:  Decrease upper bound for while using manual scaling\n";
    ss << "  =:  Increase upper bound for while using manual scaling\n";
    ss << "  -:  +shift: Decrease lower bound for while using manual scaling\n";
    ss << "  =:  +shift: Increase lower bound for while using manual scaling\n";
    ss << "  q:  Quit the program.\n";
    ss << "  r:  Toggle render mode   [SMOKE, SMOKE3D, VECTORS]\n";
    return ss.str();
}
#include "window.ih"

#include <iostream>

void Window::print_shortcuts() const
{
    cout << "Key:  Setting\n";
    cout << "  c:  Toggle color mapping [BLACKWHITE, RAINBOW, BANDS, SPACE, DUTCH]\n";
    cout << "  g:  Toggle glyph mode [NONE, GLYPH, ARROW]\n";
    cout << "  h:  Reprint this menu\n";
    cout << "  m:  Toggle color mode    [DENSITY, FORCE, VELOCITY]\n";
    cout << "  q:  Quit the program.\n";
    cout << "  r:  Toggle render mode   [SMOKE, VECTORS]\n";
    cout << "\n";
    print_settings();
}
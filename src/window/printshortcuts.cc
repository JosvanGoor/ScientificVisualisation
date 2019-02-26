#include "window.ih"

#include <iostream>

void Window::print_shortcuts() const
{
    cout << "Key:  Setting\n";
    cout << "  h:  Reprint this menu\n";
    cout << "  c:  Toggle color mapping [BLACKWHITE, RAINBOW, BANDS]\n";
    cout << "  r:  Toggle render mode   [SMOKE, VECTORS]\n";
    cout << "  m:  Toggle color mode    [DENSITY, FORCE, VELOCITY]\n";
    cout << "\n";
    print_settings();
}
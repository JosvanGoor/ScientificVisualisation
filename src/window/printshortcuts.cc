#include "window.ih"

#include <iostream>

void Window::print_shortcuts() const
{
    cout << "Key:  Setting\n";
    cout << "  h:  Reprint this menu\n";
    cout << "  c:  Toggle colormode [BLACKWHITE, RAINBOW, BANDS]\n";
    cout << "  r:  Toggle rendermode [SMOKE, VECTORS]\n";
    cout << "\n";
    print_settings();
}
#include "TStructures.hpp"

#include <ncurses.h>
#include <string>

using namespace std;

TWindow::TWindow() {}

TWindow::TWindow(int x, int y, int sizeX, int sizeY)
: x(x), y(y), sizeX(sizeX), sizeY(sizeY) {
    window = newwin(sizeY, sizeX, y, x);
}

TMenu::TMenu() {}

TMenu::TMenu(int x, int y, std::string text, int return_value)
: x(x), y(y), text(text), return_value(return_value) {}


TEvent::TEvent() {}

TEvent::TEvent(ETYPE type, unsigned time, unsigned val)
: type(type), time(time), val(val) {}

TConfig::TConfig() {}
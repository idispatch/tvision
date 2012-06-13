#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10

#include <SDL_console.h>
#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>

void THWMouseQNX::GetEvent(MouseEventType &me) {
    me.where.x = SDL_console_get_mouse_x();
    me.where.y = SDL_console_get_mouse_y();
    unsigned char buttonState = SDL_console_get_mouse_button();
    switch(buttonState) {
    case 1:
        me.buttons = mbLeftButton;
        break;
    case 2:
        me.buttons = mbRightButton;
        break;
    case 3:
        me.buttons = mbLeftButton | mbRightButton;
        break;
    default:
        me.buttons = 0;
        break;
    }
    me.doubleClick = false;
}

void THWMouseQNX::Init() {
    noMouse = false;
    oldButtonCount = buttonCount = 2;
    THWMouse::GetEvent = THWMouseQNX::GetEvent;
    Resume();
}

#else

#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>

#endif


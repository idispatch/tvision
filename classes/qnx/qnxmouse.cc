#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10

#include <SDL_console.h>
#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>

void THWMouseQNX::GetEvent(MouseEventType &me) {
    /*SDL_console_run_frames(1);*/
}

void THWMouseQNX::Init() {
    THWMouse::GetEvent = THWMouseQNX::GetEvent;
    THWMouse::Resume = THWMouseQNX::Resume;
    Resume();
}

void THWMouseQNX::Resume() {
}

#else

#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>

#endif


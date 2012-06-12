#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10
#include <console.h>
#include <SDL_console.h>
#include <tv/qnx/screen.h>

console_t g_console = NULL;

void TDisplayQNX::SetCursorPos(unsigned x, unsigned y) {
    console_cursor_goto_xy(g_console, x, y);
}

void TDisplayQNX::GetCursorPos(unsigned &x, unsigned &y) {
    x = console_get_cursor_x(g_console);
    y = console_get_cursor_y(g_console);
}

void TDisplayQNX::ClearScreen(uchar screenWidth, uchar screenHeight) {
    console_clear(g_console);
}

ushort TDisplayQNX::GetRows() {
    return console_get_height(g_console);
}

ushort TDisplayQNX::GetCols() {
    return console_get_width(g_console);
}

ushort TDisplayQNX::GetCrtMode() {
    return smCO128x37;
}

void TDisplayQNX::SetCrtMode(ushort mode) {
    switch(mode) {
    case smCO128x37:
        break;
    default:
        break;
    }
}

void TDisplayQNX::Beep() {
}

TDisplayQNX::~TDisplayQNX() {
    g_console = NULL;
    SDL_console_done();
}

void TDisplayQNX::Init() {
    if(g_console==NULL) {
        SDL_console_init(0);
        g_console = SDL_console_get();
    }
    setCursorPos = SetCursorPos;
    getCursorPos = GetCursorPos;
    getRows = GetRows;
    getCols = GetCols;
    clearScreen = ClearScreen;
    getCrtMode = GetCrtMode;
    setCrtMode = SetCrtMode;
    beep = Beep;
}

#else

#include <tv/qnx/screen.h>

#endif


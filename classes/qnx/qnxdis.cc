#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10
#include <console.h>
#include <SDL_console.h>
#include <tv/qnx/screen.h>

console_t g_console = NULL;

unsigned TDisplayQNX::cursor_shape_start = 0;
unsigned TDisplayQNX::cursor_shape_end = 0;

void TDisplayQNX::SetCursorPos(unsigned x, unsigned y) {
    console_cursor_goto_xy(g_console, x, y);
}

void TDisplayQNX::GetCursorPos(unsigned &x, unsigned &y) {
    x = console_get_cursor_x(g_console);
    y = console_get_cursor_y(g_console);
}

void TDisplayQNX::SetCursorShape(unsigned start, unsigned end) {
    cursor_shape_start = start;
    cursor_shape_end = end;
    if(cursor_shape_start == 0 && cursor_shape_end == 0) {
        console_hide_cursor(g_console);
    } else {
        console_show_cursor(g_console);
    }
}

void TDisplayQNX::GetCursorShape(unsigned &start, unsigned &end) {
    start = cursor_shape_start;
    end = cursor_shape_end;
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
    font_id_t font = console_get_font(g_console);
    switch(font) {
    case FONT_8x8:
        return smCO128x75;
    case FONT_8x10:
        return smCO128x60;
    case FONT_8x16:
        return smCO128x37;
    case FONT_9x8:
        return smCO113x75;
    case FONT_9x16:
        return smCO113x37;
    case FONT_10x20:
        return smCO102x30;
    case FONT_12x16:
        return smCO85x37;
    case FONT_12x23:
        return smCO85x26;
    case FONT_12x24:
        return smCO85x25;
    case FONT_12x27:
        return smCO85x22;
    case FONT_14x30:
        return smCO73x20;
    case FONT_16x32:
        return smCO64x18;
    case FONT_16x37:
        return smCO64x16;
    case FONT_25x57:
        return smCO40x22;
    default:
        return smCO128x75;
    }
}

void TDisplayQNX::SetCrtMode(ushort mode) {
    switch(mode) {
    case smCO128x75:
        console_set_font(g_console, FONT_8x8);
        break;
    case smCO128x60:
        console_set_font(g_console, FONT_8x10);
        break;
    case smCO128x37:
        console_set_font(g_console, FONT_8x16);
        break;
    case smCO113x75:
        console_set_font(g_console, FONT_9x8);
        break;
    case smCO113x37:
        console_set_font(g_console, FONT_9x16);
        break;
    case smCO102x30:
        console_set_font(g_console, FONT_10x20);
        break;
    case smCO85x37:
        console_set_font(g_console, FONT_12x16);
        break;
    case smCO85x26:
        console_set_font(g_console, FONT_12x23);
        break;
    case smCO85x25:
        console_set_font(g_console, FONT_12x24);
        break;
    case smCO85x22:
        console_set_font(g_console, FONT_12x27);
        break;
    case smCO73x20:
        console_set_font(g_console, FONT_14x30);
        break;
    case smCO64x18:
        console_set_font(g_console, FONT_16x32);
        break;
    case smCO64x16:
        console_set_font(g_console, FONT_16x37);
        break;
    case smCO40x22:
        console_set_font(g_console, FONT_25x57);
        break;
    default:
        console_set_font(g_console, FONT_8x8);
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
        g_console = SDL_console_init(0, FONT_12x16);
    }
    setCursorPos = SetCursorPos;
    getCursorPos = GetCursorPos;
    setCursorShape = SetCursorShape;
    getCursorShape = GetCursorShape;
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


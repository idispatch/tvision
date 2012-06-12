#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10

#include <console.h>
#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>
#include <tv/qnx/key.h>

extern console_t g_console;
bool TScreenQNX::initialized = false;

int TScreenQNX::InitOnce() {
    if(!initialized) {
        TDisplayQNX::Init();

        TScreen::System_p = TScreenQNX::System;
        TScreen::Resume = TScreenQNX::Resume;
        TScreen::Suspend = TScreenQNX::Suspend;
        TScreen::getCharacters = TScreenQNX::GetCharacters;
        TScreen::getCharacter = TScreenQNX::GetCharacter;
        TScreen::setCharacters = TScreenQNX::SetCharacters;
        TScreen::setCharacter = TScreenQNX::SetCharacter;

        TGKeyQNX::Init();
        THWMouseQNX::Init();

        if(screenBuffer!=NULL) {
            delete [] screenBuffer;
            screenBuffer = NULL;
        }
        unsigned width = console_get_width(g_console);
        unsigned height = console_get_height(g_console);
        screenBuffer = new ushort[width * height];
        memset(screenBuffer, 0, width * height * sizeof(ushort));

        initialized = true;
    }
    return 1;
}

TScreenQNX::TScreenQNX() {
    if (!InitOnce())
        return;
    Resume();
    screenMode = getCrtMode();
    setCrtData();
    suspended = 0;
}

TScreenQNX::~TScreenQNX() {
    suspend(); // High level suspend to avoid a double call
    if(screenBuffer!=NULL) {
        delete [] screenBuffer;
        screenBuffer = NULL;
    }
}

int TScreenQNX::System(const char *command,
                       pid_t *pidChild,
                       int in,
                       int out,
                       int err) {
    return 0;
}

void TScreenQNX::GetCharacters(unsigned offset, ushort * buf, unsigned count) {
    memcpy(buf, screenBuffer + offset, count*sizeof(ushort));
    /*for(;count > 0; --count) {
        *buf++ = GetCharacter(offset++);
    }*/
}

ushort TScreenQNX::GetCharacter(unsigned offset) {
    /*ushort c = (ushort)console_get_character_at_offset(g_console, offset);
    ushort a = console_get_attribute_at_offset(g_console, offset);
    return (c << 8) + a;*/
    return screenBuffer[offset];
}

void TScreenQNX::SetCharacters(unsigned offset, ushort * buf, unsigned count) {
    memcpy(screenBuffer + offset, buf, count * sizeof(ushort));
    for(;count > 0; --count) {
        SetCharacter(offset++, *buf++);
    }
}

void TScreenQNX::SetCharacter(unsigned offset, uint32 c) {
    screenBuffer[offset] = (ushort)c;
    console_set_character_and_attribute_at_offset(g_console,
                                                  offset,
                                                  (unsigned char)(c & 0xff),
                                                  (unsigned char)((c & 0xff00) >> 8));
}

void TScreenQNX::Resume() {
}

void TScreenQNX::Suspend() {
}

TScreen *TV_QNXDriverCheck() {
    return new TScreenQNX();
}

#else

#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>
#include <tv/qnx/key.h>

#endif


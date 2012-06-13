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
        TScreen::getCharacters = TScreenQNX::GetCharacters;
        TScreen::getCharacter = TScreenQNX::GetCharacter;
        TScreen::setCharacters = TScreenQNX::SetCharacters;
        TScreen::setCharacter = TScreenQNX::SetCharacter;

        TGKeyQNX::Init();
        THWMouseQNX::Init();

        unsigned width = console_get_width(g_console);
        unsigned height = console_get_height(g_console);
        screenBuffer = console_get_raw_buffer(g_console);

        initialized = true;
    }
    return 1;
}

TScreenQNX::TScreenQNX() {
    if (!InitOnce())
        return;
    screenMode = getCrtMode();
    setCrtData();
    suspended = 0;
}

int TScreenQNX::System(const char *command,
                       pid_t *pidChild,
                       int in,
                       int out,
                       int err) {
    return 0;
}

void TScreenQNX::GetCharacters(unsigned offset, ushort * buf, unsigned count) {
#ifdef _DEBUG
    unsigned max_offset = console_get_width(g_console) * console_get_height(g_console);
    if(offset + count >= max_offset) {
        fprintf(stderr,
                "Reading beyond end of console buffer (offset: %u, max: %u)\n",
                offset, max_offset);
        fflush(stderr);
    }
#endif
    memcpy(buf, screenBuffer + offset, count * sizeof(ushort));
}

ushort TScreenQNX::GetCharacter(unsigned offset) {
#ifdef _DEBUG
    unsigned max_offset = console_get_width(g_console) * console_get_height(g_console);
    if(offset >= max_offset) {
        fprintf(stderr,
                "Reading beyond end of console buffer (offset: %u, max: %u)\n",
                offset, max_offset);
        fflush(stderr);
    }
#endif
    return screenBuffer[offset];
}

void TScreenQNX::SetCharacters(unsigned offset, ushort * buf, unsigned count) {
    for(;count > 0; --count) {
        SetCharacter(offset++, *buf++);
    }
}

void TScreenQNX::SetCharacter(unsigned offset, uint32 c) {
#ifdef _DEBUG
    unsigned max_offset = console_get_width(g_console) * console_get_height(g_console);
    if(offset >= max_offset) {
        fprintf(stderr,
                "Writing beyond end of console buffer (offset: %u, max: %u)\n",
                offset, max_offset);
        fflush(stderr);
    }
#endif
    console_set_character_and_attribute_at_offset(g_console,
                                                  offset,
                                                  (unsigned char)(c & 0xff),
                                                  (unsigned char)((c & 0xff00) >> 8));
}

TScreen *TV_QNXDriverCheck() {
    return new TScreenQNX();
}

#else

#include <tv/qnx/screen.h>
#include <tv/qnx/mouse.h>
#include <tv/qnx/key.h>

#endif


#include <tv/configtv.h>
#include <tv.h>

#ifdef TVOSf_BBOS10
#include <SDL_console.h>
#include <tv/qnx/screen.h>
#include <tv/qnx/key.h>

unsigned TGKeyQNX::GetShiftState() {
    return 0;
}

void TGKeyQNX::Clear(void) {
}

int TGKeyQNX::KbHit(void) {
    SDL_console_run_frames(1);
    return 0;
}

void TGKeyQNX::FillTEvent(TEvent &e) {
}

void TGKeyQNX::Init() {
    TGKey::kbhit = KbHit;
    TGKey::getShiftState = GetShiftState;
    TGKey::fillTEvent = FillTEvent;
    TGKey::clear = Clear;
}
#else

#include <tv/qnx/screen.h>
#include <tv/qnx/key.h>

#endif

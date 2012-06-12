#ifndef QNXKEY_HEADER_INCLUDED
#define QNXKEY_HEADER_INCLUDED

// A class to encapsulate the globals, all is static!
class TGKeyQNX: public TGKey {
public:
    // Usually nothing goes here and the initialization code goes in Init()
    TGKeyQNX() {};

    // Function replacements
    // Put the keyboard in the original state
    static void Suspend();
    // Memorize current state and setup our state
    static void Resume();
    // Is a key waiting to be retrieved?
    static int KbHit();
    // Remove all the keys waiting to be retrieved.
    static void Clear();
    // Get the next key. The format is the one you can see in tkeyext.h and
    // gkey.h
    static ushort GKey();
    // What's the current state of modifier keys. The IBM BIOS values are used.
    // Not all targets implement it.
    static unsigned GetShiftState();
    // Fill a TEvent structure with the next available key (or evNothing)
    static void FillTEvent(TEvent &e);
    // Set a particular mode requested by the user. The values should be allocated
    // in the keyMode enumeration found in TGKey to avoid collisions between drivers.
    static void SetKbdMapping(int version);

    // Setup the pointers to point our members
    static void Init();
};
#endif

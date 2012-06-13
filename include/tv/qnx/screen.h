#ifndef QNXSCR_HEADER_INCLUDED
#define QNXSCR_HEADER_INCLUDED

class TDisplayQNX : virtual public TDisplay {
protected:
    TDisplayQNX() {}
    virtual ~TDisplayQNX();
    // This sets the pointers of TDisplay to point to this class.
    static void Init();

    static void SetCursorPos(unsigned x, unsigned y);
    static void GetCursorPos(unsigned &x, unsigned &y);
    static ushort GetRows();
    static ushort GetCols();
    static void SetCrtMode(ushort mode);
    static ushort GetCrtMode();
    static void ClearScreen(uchar screenWidth, uchar screenHeight);
    static void Beep();
};

class TScreenQNX : public TDisplayQNX, public TScreen {
public:
    TScreenQNX();

    // Usually our guts are needed by the key, mouse and/or display.
    // Here you can allow access to those classes.
    friend class TGKeyQNX;
    friend class THWMouseQNX;
    friend class TDisplayQNX;

protected:
    static void Resume();
    static void Suspend();
    static void GetCharacters(unsigned offset, ushort * buf, unsigned count);
    static ushort GetCharacter(unsigned offset);
    static void SetCharacters(unsigned offset, ushort * buf, unsigned count);
    static void SetCharacter(unsigned offset, uint32 c);
    static int System(const char *command,
                       pid_t *pidChild,
                       int in,
                       int out,
                       int err);
    int InitOnce();
private:
    static bool initialized;
};

TScreen *TV_QNXDriverCheck();

#endif


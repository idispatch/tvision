#ifndef QNXMOUSE_HEADER_INCLUDED
#define QNXMOUSE_HEADER_INCLUDED

class THWMouseQNX : public THWMouse {
public:
    static void Init();
protected:
    static void GetEvent(MouseEventType &me);
};

#endif


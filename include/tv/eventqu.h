/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H�hne to be used for RHIDE.

 *
 *
 */

#ifndef __TEventQueue
#define __TEventQueue

class TEventQueue
{
public:
    TEventQueue();
    ~TEventQueue();

    static void getMouseEvent( TEvent& );
    static void suspend();
    static void resume();

    friend class TView;
    friend void genRefs();
    friend class TProgram;
    static ushort doubleDelay;
    static Boolean mouseReverse;

private:

    static TMouse *mouse;
    static void getMouseState( TEvent& );
    static void mouseInt();

    static void setLast( TEvent& );

    static MouseEventType lastMouse;
public:
    static MouseEventType curMouse;
private:
    static MouseEventType downMouse;
    static ushort downTicks;

    static ushort * Ticks;
    static TEvent eventQueue[ eventQSize ];
    static TEvent * eventQHead;
    static TEvent * eventQTail;
    static Boolean mouseIntFlag;
    static ushort eventCount;

    static Boolean mouseEvents;

    static ushort repeatDelay;
    static ushort autoTicks;
    static ushort autoDelay;

    friend class THWMouse;
    friend class THWMouseDOS;
};

inline void TEvent::getMouseEvent()
{
    TEventQueue::getMouseEvent( *this );
}

#endif


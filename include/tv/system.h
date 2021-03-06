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

#ifndef __EVENT_CODES
#define __EVENT_CODES

/* Event codes */

const ushort evMouseDown = 0x0001;
const ushort evMouseUp   = 0x0002;
const ushort evMouseMove = 0x0004;
const ushort evMouseAuto = 0x0008;
const ushort evKeyDown   = 0x0010;
const ushort evCommand   = 0x0100;
const ushort evBroadcast = 0x0200;

/* Event masks */

const ushort evNothing   = 0x0000;
const ushort evMouse     = 0x000f;
const ushort evKeyboard  = 0x0010;
const ushort evMessage   = 0xFF00;

/* Mouse button state masks */
/* SET: Note that I redefined them to make it coherent with most UNIX systems
   where the left button is the first, the middle one the second, etc. But safe
   code shouldn't rely on it. */
const ushort mbLeftButton  = 0x01;
const ushort mbMiddleButton= 0x02;
const ushort mbRightButton = 0x04;
const ushort mbButton4     = 0x08;
const ushort mbButton5     = 0x10;

#endif

#include <tv/event.h>
#include <tv/eventqu.h>
#include <tv/screen.h>


/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.

 *
 *
 */

#ifndef __COLOR_COMMAND_CODES
#define __COLOR_COMMAND_CODES

const ushort
  cmColorForegroundChanged = 71,
  cmColorBackgroundChanged = 72,
  cmColorSet               = 73,
  cmNewColorItem           = 74,
  cmNewColorIndex          = 75,
  cmTryColors              = 76,
  cmUpdateColorsChanged    = 77;

#endif  // __COLOR_COMMAND_CODES

class TColorItem;
class TColorGroup;

TColorItem& operator + ( TColorItem& i1, TColorItem& i2 );
TColorGroup& operator + ( TColorGroup& g, TColorItem& i );
TColorGroup& operator + ( TColorGroup& g1, TColorGroup& g2 );

#include <tv/clritem.h>
#include <tv/clrgroup.h>
#include <tv/clrselct.h>
#include <tv/mnoselct.h>
#include <tv/clrdisp.h>
#include <tv/clrgrpli.h>
#include <tv/clriteml.h>
#include <tv/clrdlg.h>


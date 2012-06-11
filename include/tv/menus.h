/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.
Modified by Salvador E. Tropea: Added += operators.

 *
 *
 */

class TSubMenu;
class TMenuItem;
class TStatusDef;
class TStatusItem;

TSubMenu& operator + ( TSubMenu& s, TMenuItem& i );
TSubMenu& operator + ( TSubMenu& s1, TSubMenu& s2 );
TStatusDef& operator + ( TStatusDef& s1, TStatusItem& s2 );
TStatusDef& operator + ( TStatusDef& s1, TStatusDef& s2 );

#include <tv/menuitem.h>
#include <tv/submenu.h>
#include <tv/menu.h>
#include <tv/menuview.h>
#include <tv/menubar.h>
#include <tv/menubox.h>
#include <tv/statsitm.h>
#include <tv/statsdef.h>
#include <tv/statslin.h>

// SET: The following 4 operator are from TVTools
// They are simple and adds more coherence.
#ifndef TSubMenu_operators_defined
#define TSubMenu_operators_defined
inline void operator += ( TSubMenu& s1, TSubMenu& s2 )
{
    s1 = s1 + s2;
}
#endif

#ifndef TSubMenu_Item_operators_defined
#define TSubMenu_Item_operators_defined
inline void operator += ( TSubMenu& i1, TMenuItem& i2 )
{
    i1 = i1 + i2;
}
#endif

#ifndef TStatusDef_operators_defined
#define TStatusDef_operators_defined
inline void operator += ( TStatusDef& s1, TStatusDef& s2 )
{
    s1 = s1 + s2;
}
#endif


#ifndef TStatusDef_Item_operators_defined
#define TStatusDef_Item_operators_defined
inline void operator += ( TStatusDef& s1, TStatusItem& s2 )
{
    s1 = s1 + s2;
}
#endif


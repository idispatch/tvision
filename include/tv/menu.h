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

#ifndef __TMenu
#define __TMenu

class TMenuItem;

class TMenu
{

public:
    TMenu() : items(0), deflt(0) {};
    TMenu( TMenuItem& itemList )
        { items = &itemList; deflt = &itemList; }
    TMenu( TMenuItem& itemList, TMenuItem& TheDefault )
        { items = &itemList; deflt = &TheDefault; }
    ~TMenu();

    TMenuItem *items;
    TMenuItem *deflt;

};

#endif


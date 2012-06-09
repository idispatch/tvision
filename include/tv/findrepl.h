/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *

 Modified by Robert H”hne to be used for RHIDE.

 *
 *
 */

#ifndef __TFindDialogRec
#define __TFindDialogRec
#include <string.h>

struct TFindDialogRec {
    TFindDialogRec(const char *str, ushort flgs) {
        strcpy(find, str);
        options = flgs;
    }
    char find[maxFindStrLen];
    ushort options;
};

#endif

#ifndef __TReplaceDialogRec
#define __TReplaceDialogRec

struct TReplaceDialogRec
{
    TReplaceDialogRec( const char *str, const char *rep, ushort flgs )
    {
        strcpy( find, str );
        strcpy( replace, rep );
        options = flgs;
    }
    char find[maxFindStrLen];
    char replace[maxReplaceStrLen];
    ushort options;
};

#endif

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
#include <tv.h>

#if defined(TVCompf_djgpp)
#include <dir.h>
#endif
#if defined(TVComp_BCPP)
#include <dir.h>
#include <dos.h>
#endif

TFileInputLine::TFileInputLine(const TRect& bounds, short aMaxLen) :
        TInputLine(bounds, aMaxLen) {
    eventMask = eventMask | evBroadcast;
}

/**[txh]********************************************************************

 Description:
 Simple routine to join three strings without coping more than max+1 bytes.
 The data buffer must support max+1 bytes. The s2 and s3 parameters can be
 NULL.@p
 It could be implemented with var_args, any interest?

 ***************************************************************************/

static
int strCat(char *d, char const *s1, char const *s2, char const *s3, int max) {
    char *dest = d;
    char *end = dest + max;

    for (; *s1 && dest < end; s1++)
        *(dest++) = *s1;
    if (s2)
        for (; *s2 && dest < end; s2++)
            *(dest++) = *s2;
    if (s3)
        for (; *s3 && dest < end; s3++)
            *(dest++) = *s3;
    *dest = 0;
    return dest - d;
}

void TFileInputLine::handleEvent(TEvent& event) {
    TInputLine::handleEvent(event);
    if (event.what == evBroadcast && event.message.command == cmFileFocused
            && !(state & sfSelected)) {
        if ((((TSearchRec *) event.message.infoPtr)->attr & FA_DIREC) != 0)
            dataLen = strCat(data, ((TSearchRec *) event.message.infoPtr)->name, DIRSEPARATOR_,
                    ((TFileDialog *) owner)->wildCard, maxLen);
        else
            dataLen = strCat(data, ((TSearchRec *) event.message.infoPtr)->name, 0, 0, maxLen);
        drawView();
    }
}

#if !defined( NO_STREAM )
TFileInputLine::TFileInputLine( StreamableInit ) :
TInputLine( streamableInit)
{
}

TStreamable *TFileInputLine::build()
{
    return new TFileInputLine( streamableInit );
}
#endif // NO_STREAM

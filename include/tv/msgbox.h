/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *

Modified by Robert H”hne to be used for RHIDE.
Modified by Salvador E. Tropea.

 *
 *
 */

#ifndef __MsgBox
#define __MsgBox

#if !defined( __STDARG_H )
#include <stdarg.h>
#endif  // __STDARG_H

ushort messageBox( const char *msg, ushort aOptions );
ushort messageBox( ushort aOptions, const char *msg, ... )
                __attribute__ ((format (printf, 2, 3)));

ushort messageBoxRect( const TRect &r, const char *msg, ushort aOptions );
ushort messageBoxRect( const TRect &r, ushort aOptions, const char *msg, ... )
                __attribute__ ((format (printf, 3, 4)));

ushort inputBox( const char *Title, const char *aLabel, char *s, int limit );

ushort inputBoxRect( const TRect &bounds, const char *title,
                     const char *aLabel, char *s, int limit );

const ushort

//  Message box classes

    mfWarning      = 0x0000,       // Display a Warning box
    mfError        = 0x0001,       // Dispaly a Error box
    mfInformation  = 0x0002,       // Display an Information Box
    mfConfirmation = 0x0003,       // Display a Confirmation Box

// Message box button flags

    mfYesButton    = 0x0100,       // Put a Yes button into the dialog
    mfNoButton     = 0x0200,       // Put a No button into the dialog
    mfOKButton     = 0x0400,       // Put an OK button into the dialog
    mfCancelButton = 0x0800,       // Put a Cancel button into the dialog

// Special flag: Avoid translating this message, is already translated.
    mfDontTranslate = 0x4000,
// Special flag: For the "Don't show it next time" field
    mfDontShowAgain = 0x8000,

    mfYesNoCancel  = mfYesButton | mfNoButton | mfCancelButton,
                                    // Standard Yes, No, Cancel dialog
    mfOKCancel     = mfOKButton | mfCancelButton;
                                    // Standard OK, Cancel dialog

#endif



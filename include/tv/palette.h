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

#ifndef __TPalette
#define __TPalette

class TPalette {

public:

    TPalette(const char *, ushort);
    TPalette(const TPalette&);
    ~TPalette();
    TPalette& operator =(const TPalette&);
    uchar& operator[](int index) const {
        return data[index];
    }

    uchar *data;

};

#endif


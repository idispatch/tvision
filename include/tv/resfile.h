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

#ifndef __TResourceFile
#define __TResourceFile

#if !defined( NO_STREAM )
class TResourceFile: public TObject
{

public:

    TResourceFile( fpstream *aStream );
    ~TResourceFile();
    short count();
    void remove( const char *key );
    void flush();
    void *get( const char *key );
    const char *keyAt( short i );
    void put( TStreamable *item, const char *key );
    fpstream *switchTo( fpstream *aStream, Boolean pack );

protected:

    fpstream *stream;
    Boolean modified;
    CLY_StreamPosT basePos;
    CLY_StreamPosT indexPos;
    TResourceCollection *index;
};
#endif
#endif


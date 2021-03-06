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

#ifndef __TStringList
#define __TStringList

class TStrIndexRec;

const int MAXKEYS = 16;

class TStringList : public TObject
#if !defined( NO_STREAM )
                  , public TStreamable
#endif // NO_STREAM
{

public:

    ~TStringList();
#if !defined( NO_STREAM )
    void get( char *dest, ushort key );
#endif
private:

    long basePos;
    short indexSize;
    TStrIndexRec *index;
#if !defined( NO_STREAM )
    ipstream *ip;

    virtual const char *streamableName() const
	{ return name; }

protected:

    TStringList( StreamableInit );
    virtual void write( opstream& ) {}
    virtual void *read( ipstream& );

public:

    static const char * const name;
    static TStreamable *build();
#endif // NO_STREAM
};

#if !defined( NO_STREAM )
inline ipstream& operator >> ( ipstream& is, TStringList& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TStringList*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TStringList& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TStringList* cl )
    { return os << (TStreamable *)cl; }
#endif // NO_STREAM

#endif


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

#ifndef __TColorDisplay
#define __TColorDisplay

class TColorDisplay : public TView
{

public:

    TColorDisplay( const TRect& bounds, const char *aText );
    virtual ~TColorDisplay();
    virtual void draw();
    virtual void handleEvent( TEvent& event );
    virtual void setColor( uchar *aColor );

protected:

    uchar *color;
    const char *text;

#if !defined( NO_STREAM )
private:

    virtual const char *streamableName() const
        { return name; }

protected:

    TColorDisplay( StreamableInit );
    virtual void write( opstream& );
    virtual void *read( ipstream& );

public:

    static const char * const name;
    static TStreamable *build();
#endif
};

#if !defined( NO_STREAM )
inline ipstream& operator >> ( ipstream& is, TColorDisplay& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TColorDisplay*& cl )
    { return is >> (void *&)cl; }

inline opstream& operator << ( opstream& os, TColorDisplay& cl )
    { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TColorDisplay* cl )
    { return os << (TStreamable *)cl; }
#endif
#endif


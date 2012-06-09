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
#include <tv.h>

#define cpIndicator "\x02\x03"

TIndicator::TIndicator( const TRect& bounds ) :
    TView( bounds )
{
    growMode = gfGrowLoY | gfGrowHiY;
    location.x = location.y = 1;
}

void TIndicator::draw()
{
    uchar color, frame;
    TDrawBuffer b;
    char s[15];

    if( (state & sfDragging) == 0 )
        {
        color = getColor(1);
        frame = dragFrame;
        }
    else
        {
        color = getColor(2);
        frame = normalFrame;
        }

    b.moveChar( 0, frame, color, size.x );
    if( modified )
        b.putChar( 0, modifiedStar );
    sprintf(s," %d:%d ",location.y+1,location.x+1);
    b.moveCStr( 8-int(strchr(s, ':')-s), s, color);
    writeBuf(0, 0, size.x, 1, b);
}

TPalette& TIndicator::getPalette() const
{
    static TPalette palette( cpIndicator, sizeof( cpIndicator )-1 );
    return palette;
}

void TIndicator::setState( ushort aState, Boolean enable )
{
    TView::setState(aState, enable);
    if( aState == sfDragging )
        drawView();
}

void TIndicator::setValue( const TPoint& aLocation, Boolean aModified )
{
    if( (location !=  aLocation) || (modified != aModified) )
        {
        location = aLocation;
        modified = aModified;
        drawView();
        }
}

#if !defined( NO_STREAM )
TStreamable *TIndicator::build()
{
    return new TIndicator( streamableInit );
}

TIndicator::TIndicator( StreamableInit ) : TView( streamableInit )
{
}
#endif // NO_STREAM


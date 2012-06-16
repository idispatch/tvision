/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.
 * Modified by Salvador E. Tropea to compile for 64 bits architectures.
 *
 *
 */
#include <tv.h>

const uchar monoColors[] = { 0x07, 0x0F, 0x01, 0x70, 0x09 };

TMonoSelector::TMonoSelector( const TRect& bounds ) :
    TCluster( bounds, new TSItem( _("Normal"),
                      new TSItem( _("Highlight"),
                      new TSItem( _("Underline"),
                      new TSItem( _("Inverse"),  0 )))))
{
    eventMask |= evBroadcast;
}

void TMonoSelector::draw()
{
    drawBox( button, 0x07 );
}

void TMonoSelector::handleEvent( TEvent& event )
{
    TCluster::handleEvent( event );
    if( event.what == evBroadcast && event.message.command == cmColorSet )
        {
        value = event.message.infoLong;
        drawView();
        }
}

Boolean TMonoSelector::mark( int item )
{
    return Boolean(monoColors[item] == (uchar)value);
}

void TMonoSelector::newColor()
{
    message( owner, evBroadcast, cmColorForegroundChanged,
        (void *)(long)(value & 0x0F) );
    message( owner, evBroadcast, cmColorBackgroundChanged,
        (void *)(long)((value >> 4) & 0x0F));
}

void TMonoSelector::press( int item )
{
    value = monoColors[item];
    newColor();
}

void TMonoSelector::movedTo( int item )
{
    value = monoColors[item];
    newColor();
}

#if !defined( NO_STREAM )
TStreamable *TMonoSelector::build()
{
    return new TMonoSelector( streamableInit );
}

TMonoSelector::TMonoSelector( StreamableInit ) : TCluster( streamableInit )
{
}
#endif // NO_STREAM



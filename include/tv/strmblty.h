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

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   class TStreamableTypes                                                */
/*                                                                         */
/*   Maintains a database of all registered types in the application.      */
/*   Used by opstream and ipstream to find the functions to read and       */
/*   write objects.                                                        */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef __TStreamableTypes
#define __TStreamableTypes

#if !defined ( NO_STREAM )
// Avoid replacing new by MSS's macro
#include <tv/no_mss.h>

class TStreamableTypes : private TNSSortedCollection
{

public:

    TStreamableTypes();
    ~TStreamableTypes();

    void registerType( const TStreamableClass * );
    const TStreamableClass *lookup( const char * );

    void *operator new( size_t sz ) { return ::operator new( sz ); }
    void *operator new( size_t, void * );

private:

    virtual void *keyOf( void * );
    int compare( void *, void * );

};

#include <tv/yes_mss.h>
#endif

#endif


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

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   class TPWrittenObjects                                                */
/*                                                                         */
/*   Maintains a database of all objects that have been written to the     */
/*   current object stream.                                                */
/*                                                                         */
/*   Used by opstream when it writes a pointer onto a stream to determine  */
/*   whether the object pointed to has already been written to the stream. */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef __TPWrittenObjects
#define __TPWrittenObjects

#if !defined ( NO_STREAM )
class TPWrittenObjects : public TNSSortedCollection
{

    friend class opstream;

public:

    void removeAll() { curId = 0; TNSSortedCollection::removeAll(); }

private:

    TPWrittenObjects();
    ~TPWrittenObjects();

    void registerObject( const void *adr );
    P_id_type find( const void *adr );

    void *keyOf( void * );
    int compare( void *, void * );
    void freeItem( void *item ); // Note: Just to use delete instead of delete[]

    P_id_type curId;

};

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   class TPWObj                                                          */
/*                                                                         */
/*   Used internally by TPWrittenObjects.                                  */
/*                                                                         */
/* ------------------------------------------------------------------------*/

class TPWObj
{

    friend class TPWrittenObjects;

private:

    TPWObj( const void *adr, P_id_type id );

    const void *address;
    P_id_type ident;

};
#endif

#endif


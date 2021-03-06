/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H�hne to be used for RHIDE.
Modified to compile with gcc v3.x by Salvador E. Tropea, with the help of
Andris Pavenis and Christoph Bauer.

 *
 *
 */

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   class fpstream                                                        */
/*                                                                         */
/*   Base class for reading and writing streamable objects to              */
/*   bidirectional file streams                                            */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef __fpstream
#define __fpstream 1
#if !defined( NO_STREAM )
class fpstream : public fpbase, public iopstream
{
public:
    fpstream();
    fpstream( const char *, CLY_OpenModeT, int = CLY_FBOpenProtDef );
    fpstream( int );
    fpstream( int, char *, int );
    ~fpstream();
    long filelength();

    CLY_filebuf *rdbuf();
    void open( const char *, CLY_OpenModeT, int = CLY_FBOpenProtDef );
};
#endif
#endif


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

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   class iopstream                                                       */
/*                                                                         */
/*   Base class for reading and writing streamable objects                 */
/*                                                                         */
/* ------------------------------------------------------------------------*/

#ifndef __iopstream
#define __iopstream

#if !defined( NO_STREAM )
class iopstream : public ipstream, public opstream
{
public:
 iopstream(CLY_streambuf *);
 ~iopstream();

protected:
 iopstream();
};
#endif

#endif


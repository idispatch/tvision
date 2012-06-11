/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *
 * Modified by Robert H”hne to be used for RHIDE.
 * Modified to compile with gcc v3.x by Salvador E. Tropea, with the help of
 * Andris Pavenis.
 *
 *
 */

#include <tv.h>

#if !defined( NO_STREAM )
UsingNamespaceStd

iopstream::iopstream( CLY_streambuf * sb )
{
    pstream::init( sb );
}

iopstream::~iopstream()
{
}

iopstream::iopstream()
{
}
#endif

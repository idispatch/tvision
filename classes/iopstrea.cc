/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *

Modified by Robert H”hne to be used for RHIDE.
Modified to compile with gcc v3.x by Salvador E. Tropea, with the help of
Andris Pavenis.

 *
 *
 */

#define Uses_pstream
#define Uses_iopstream
#include <tv.h>

UsingNamespaceStd
#if !defined( NO_STREAM )
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

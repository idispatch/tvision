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

typedef unsigned P_id_type;

// SET: Here we implement a trick to pull the needed TStreamableClass-es.
// We have two approaches:
// 1) We create a structure with a pointer to itself and another to the
//    object to register the stream for the class.
// 2) Same but we use a constructor in the structure.
// The first methode was tested with gcc 2.6.3 to 3.4.1. It seems to fail
// for gcc 3.4.1, but we know it works for most versions of gcc.
// The second was specifically created to BC++ compiler.
// The BC++ approach should work for any C++ compiler, but I can't be sure.
// For this reason I'm keeping both and switching to the second approach
// only for gcc>=3.4.
// After the v2.0.3 release we could try to test if (2) is supported by all
// targets.

#undef TV_Use_Constructor_For_fLink_def
#if defined(TVComp_BCPP) || (__GNUC__>=3 && __GNUC_MINOR__>=4)
 #define TV_Use_Constructor_For_fLink_def 1
#else
 #define TV_Use_Constructor_For_fLink_def 0
#endif

#if !defined(TV__fLink_def)
#define TV__fLink_def
struct fLink
{
    fLink *f;
    class TStreamableClass *t;
    #if TV_Use_Constructor_For_fLink_def
    fLink(fLink* af, class TStreamableClass *at) : f(af), t(at) {}
    #endif
};
#endif

#if TV_Use_Constructor_For_fLink_def
#define __link( s )             \
  extern TStreamableClass s;    \
  static fLink force ## s       \
    ( (fLink *)&force ## s, (TStreamableClass *)&s );
#else
#define __link( s )             \
  extern TStreamableClass s;    \
  static fLink force ## s =     \
    { (fLink *)&force ## s, (TStreamableClass *)&s };
#endif

#include <tv/streambl.h>
#include <tv/strmblcl.h>
#include <tv/strmblty.h>
#include <tv/pwritobj.h>
#include <tv/preadobj.h>
#include <tv/pstream.h>
#include <tv/ipstream.h>
#include <tv/opstream.h>
#include <tv/iopstrm.h>
#include <tv/fpbase.h>
#include <tv/ifpstrm.h>
#include <tv/ofpstrm.h>
#include <tv/fpstream.h>


/*
 Copyright (c) 2000-2001 by Salvador E. Tropea.
 This file was heavily restructured.
*/

#ifndef __TTYPES_H
#define __TTYPES_H

const char EOS = '\0';

#if !defined( NO_STREAM )
enum StreamableInit { streamableInit };

class ipstream;
class opstream;
class TStreamable;
class TStreamableTypes;
#endif

typedef int32 ccIndex;
typedef Boolean (*ccTestFunc)( void *, void * );
typedef void (*ccAppFunc)( void *, void * );

const int ccNotFound = -1;

#endif

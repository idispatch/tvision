#ifndef NO_STREAM

#define Uses_TStaticText

#include <tv.h>
__link( RView )

TStreamableClass RStaticText( TStaticText::name,
                              TStaticText::build,
                              __DELTA(TStaticText)
                            );

#endif


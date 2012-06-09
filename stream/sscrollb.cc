#ifndef NO_STREAM

#define Uses_TScrollBar

#include <tv.h>
__link( RView )

TStreamableClass RScrollBar( TScrollBar::name,
                              TScrollBar::build,
                              __DELTA(TScrollBar)
                           );

#endif


#ifndef NO_STREAM

#define Uses_TMenuView

#include <tv.h>
__link( RView )

TStreamableClass RMenuView( TMenuView::name,
                            TMenuView::build,
                            __DELTA(TMenuView)
                          );

#endif


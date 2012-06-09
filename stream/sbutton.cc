#ifndef NO_STREAM

#define Uses_TButton

#include <tv.h>
__link( RView )

TStreamableClass RButton( TButton::name,
                          TButton::build,
                          __DELTA(TButton)
                        );

#endif


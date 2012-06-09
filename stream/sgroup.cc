#ifndef NO_STREAM

#define Uses_TGroup

#include <tv.h>
__link( RView )

TStreamableClass RGroup( TGroup::name,
                         TGroup::build,
                         __DELTA(TGroup)
                       );

#endif


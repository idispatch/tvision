#ifndef NO_STREAM

#define Uses_TListBox

#include <tv.h>
__link( RListViewer )

TStreamableClass RListBox( TListBox::name,
                           TListBox::build,
                           __DELTA(TListBox)
                         );

#endif


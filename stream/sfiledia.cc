#ifndef NO_STREAM

#define Uses_TFileDialog

#include <tv.h>
__link( RDialog )
__link( RFileInputLine )
__link( RFileList )

TStreamableClass RFileDialog( TFileDialog::name,
                              TFileDialog::build,
                              __DELTA(TFileDialog)
                            );

#endif


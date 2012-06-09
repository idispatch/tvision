/*
 *      Turbo Vision - Version 2.0
 *
 *      Copyright (c) 1994 by Borland International
 *      All Rights Reserved.
 *

Modified by Robert H”hne to be used for RHIDE.

 *
 *
 */

#ifndef __TApplication
#define __TApplication

class TApplication : public TProgram
{

protected:

    TApplication();
    virtual ~TApplication();

    virtual void suspend();
    virtual void resume();

};

#endif

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

#include <tv.h>

TScreen *TProgInit::tscreen = NULL;
TVMainConfigFile *TProgInit::config = NULL;

TProgInit::TProgInit(TStatusLine *(*cStatusLine)(TRect), TMenuBar *(*cMenuBar)(TRect),
        TDeskTop *(*cDeskTop)(TRect)) :
        createStatusLine(cStatusLine),
        createMenuBar(cMenuBar),
        createDeskTop(cDeskTop) {
    // Load the configuration file
    if (!config)
        config = new TVMainConfigFile();
    config->Load();
    // Read common settings
    long aux;
    if (config->Search("ShowCursorEver", aux))
        TScreen::setShowCursorEver(aux ? True : False);
    if (config->Search("DontMoveHiddenCursor", aux))
        TScreen::setDontMoveHiddenCursor(aux ? True : False);

    tscreen = new TScreen();
}

TProgInit::~TProgInit() {
    delete tscreen;
    delete config;
    tscreen = NULL;
    config = NULL;
}

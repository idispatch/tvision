/* Modified by Robert Hoehne and Salvador Eduardo Tropea for the gcc port */
/* Modified by Vadim Beloborodov to be used on WIN32 console */
/* Modified to compile with gcc v3.x by Salvador E. Tropea, with the help of
 Andris Pavenis. */
/*----------------------------------------------------------*/
/*                                                          */
/*   Turbo Vision 1.0                                       */
/*   Copyright (c) 1991 by Borland International            */
/*                                                          */
/*   Turbo Vision TVEDIT source file                        */
/*----------------------------------------------------------*/
#include <tv.h>

UsingNamespaceStd

TEditWindow *clipWindow;

TEditWindow *TEditorApp::openEditor(const char *fileName, Boolean visible) {
    TRect r = deskTop->getExtent(); //TRect(0,0,80,6);
    TView *p = validView(new TEditWindow(r, fileName, wnNoNumber));
    if (!visible)
        p->hide();
    deskTop->insert(p);
    return (TEditWindow *) p;
}

TEditorApp::TEditorApp() :
        TProgInit(TEditorApp::initStatusLine, TEditorApp::initMenuBar, TEditorApp::initDeskTop), TApplication() {

    TCommandSet ts;
    ts.enableCmd(cmSave);
    ts.enableCmd(cmSaveAs);
    ts.enableCmd(cmCut);
    ts.enableCmd(cmCopy);
    ts.enableCmd(cmPaste);
    ts.enableCmd(cmClear);
    ts.enableCmd(cmUndo);
    ts.enableCmd(cmFind);
    ts.enableCmd(cmReplace);
    ts.enableCmd(cmSearchAgain);
    disableCommands(ts);

    TEditor::editorDialog = doEditDialog;
    clipWindow = openEditor(0, False);
    if (clipWindow != 0) {
        TEditor::clipboard = clipWindow->editor;
        TEditor::clipboard->canUndo = False;
    }
}

void TEditorApp::fileOpen() {
    char fileName[PATH_MAX];
    strcpy(fileName, "*");

    if (execDialog(new TFileDialog("*", "Open file", "~N~ame", fdOpenButton, 100), fileName)
            != cmCancel)
        openEditor(fileName, True);
}

void TEditorApp::fileNew() {
    openEditor(0, True);
}

void TEditorApp::changeDir() {
    execDialog(new TChDirDialog(cdNormal, 0), 0);
}

void TEditorApp::dosShell() {
    if (TScreen::noUserScreen())
        return;
    suspend();
    TScreen::System(CLY_GetShellName());
    resume();
    redraw();
}

void TEditorApp::showClip() {
    clipWindow->select();
    clipWindow->show();
}

void TEditorApp::tile() {
    deskTop->tile(deskTop->getExtent());
}

void TEditorApp::cascade() {
    deskTop->cascade(deskTop->getExtent());
}

void TEditorApp::handleEvent(TEvent& event) {
    TApplication::handleEvent(event);
    if (event.what != evCommand)
        return;
    else
        switch (event.message.command) {
        case cmOpen:
            fileOpen();
            break;

        case cmNew:
            fileNew();
            break;

        case cmChangeDrct:
            changeDir();
            break;

        case cmCallShell:
            dosShell();
            break;

        case cmShowClip:
            showClip();
            break;

        case cmTile:
            tile();
            break;

        case cmCascade:
            cascade();
            break;

        default:
            return;
        }
    clearEvent(event);
}

#ifdef TEST
int main(int argc, char *argv[])
{
    TEditorApp *myApp=new TEditorApp();
    if (myApp)
    {
        myApp->run();
        delete myApp;
    }
    return 0;
}
#endif

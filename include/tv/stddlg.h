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

#ifndef __FILE_CMDS
#define __FILE_CMDS

const ushort

//  Commands

    cmFileOpen     = 1001,   // Returned from TFileDialog when Open pressed
    cmFileReplace  = 1002,   // Returned from TFileDialog when Replace pressed
    cmFileClear    = 1003,   // Returned from TFileDialog when Clear pressed
    cmFileInit     = 1004,   // Used by TFileDialog internally
    cmChangeDir    = 1005,   // Used by TChDirDialog internally
    cmRevert       = 1006,   // Used by TChDirDialog internally
    cmFileSelect   = 1007,   // Returned from TFileDialog when Select pressed
    cmDirSelection = 1008,   // New: Used by TChDirDialog internally and
                             // TDirListBox externally

//  Messages

    cmFileFocused = 102,    // A new file was focused in the TFileList
    cmFileDoubleClicked     // A file was selected in the TFileList
            = 103;

#endif  // __FILE_CMDS

#include <tv/searchrc.h>
#include <tv/filinpln.h>
#include <tv/filecoll.h>
#include <tv/sortlibo.h>
#include <tv/filelist.h>
#include <tv/filinfpn.h>
#include <tv/filedlg.h>
#include <tv/direntr.h>
#include <tv/dircoll.h>
#include <tv/dirlibo.h>
#include <tv/chdirdlg.h>


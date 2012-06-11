/* Copyright (C) 2000 Salvador E. Tropea */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <cl/needs.h>

#ifdef NEEDS_MKSTEMP
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <io.h>
#include <string.h>

int mkstemp (char *_template)
{
    char tmp_name[FILENAME_MAX];
    int fd = -1;

    /* Make sure we create a non-existing file, even
     if race conditions exist with other processes.  */
    do {
        strcpy(tmp_name, _template);
        errno = 0;
    }while (mktemp (tmp_name) != NULL
            /* SAA: changed file mode from 0 to 0666 because on WinNT it created files
             * with read-only attribute set. Fix me if it causes problems on other
             * platforms.
             */
            && (fd = open(tmp_name, O_RDWR | O_CREAT | O_EXCL | O_BINARY, 0666)) == -1
            && errno == EEXIST);

    if (fd == -1)
    errno = ENOENT;
    else
    strcpy(_template, tmp_name);

    return fd;
}
#endif

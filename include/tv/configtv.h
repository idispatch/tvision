/* Generated automatically by the configure script */

/* ncurses library */
#undef HAVE_NCURSES

/* ncurses 4.2 or better have define_key (In Linux) */
#undef HAVE_DEFINE_KEY

/* The X11 keysyms are there */
#undef HAVE_KEYSYMS

/* X11 library and headers */
#undef HAVE_X11

/* International support with gettext */
#undef HAVE_INTL_SUPPORT

/* GPM mouse support */
#undef HAVE_GPM

/* out/in functions defined by glibc */
/*#define HAVE_OUTB_IN_SYS 1*/

/* Use stream replacements */
/*#define HAVE_SSC 1*/

/* Byte order for this machine */
/*#define TV_BIG_ENDIAN 1*/

/* Linux implementation of POSIX threads */
/*#define HAVE_LINUX_PTHREAD 1*/

/* Memcpy doesn't support overlaps */
/*#define HAVE_UNSAFE_MEMCPY 1*/
#if 0
#define TVOS_UNIX
#define TVOSf_Linux
#define TVCPU_x86
#define TVComp_GCC
#define TVCompf_

#define TVCONFIG_RHIDE_STDINC "/usr/include /usr/local/include /usr/include/g++ /usr/local/include/g++ /usr/lib/gcc-lib /usr/local/lib/gcc-lib /usr/X11R6/include"
#define TVCONFIG_TVSRC "../../include /usr/src/tvision/include /usr/include/rhtvision "
#define TVCONFIG_RHIDE_OS_LIBS "stdc++ ncurses m gpm X11 Xmu"
#define TVCONFIG_TVOBJ "/usr/lib ../../makes /usr/src/tvision/makes /usr/X11R6/lib "
#define TVCONFIG_STDCPP_LIB "-lstdc++"
#define TVCONFIG_SHARED_CODE_OPTION "-fPIC"
#define TVCONFIG_RHIDE_LDFLAGS "-shared -Wl,-soname,librhtv.so.2.0.3 -L/usr/X11R6/lib -lX11 -lXmu -lgpm -lncurses -lstdc++ -lm -lc"
#define TVCONFIG_LIB_VER "2.0.3"
#define TVCONFIG_LIB_VER_MAJOR "2"
#define TVCONFIG_EXTRA_INCLUDE_DIRS "/usr/X11R6/include"
#define TVCONFIG_CFLAGS   "-O2 -Wall -Werror -gstabs+3 -pipe"
#define TVCONFIG_CXXFLAGS "-O2 -Wall -Werror -gstabs+3 -pipe"
#define TVCONFIG_REF_DIR  "/usr/src/tvision"
#else
#define TVComp_GCC
#define TVOS_UNIX
#define TVOSf_QNX4
#endif


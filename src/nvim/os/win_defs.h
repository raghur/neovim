#ifndef NVIM_OS_WIN_DEFS_H
#define NVIM_OS_WIN_DEFS_H

#include "auto/config.h"

#ifndef LC_MESSAGES
// FIXME(equalsraf): this is a hack - also used in ex_cmds2.c to build in
// windows without libintl
# define LC_MESSAGES LC_COLLATE
#endif

// winsock2.h must be before windows.h - or so says Mingw
#include <winsock2.h>
#include <windows.h>
// We have our own RGB macro in macros.h
#undef RGB

#include <io.h>
#include <uv.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

// FIXME(equalsraf): this is only used by if_cscope.c
#ifndef S_ISLNK
# define S_ISLNK(mode) 0
#endif

// For MSVC
#ifdef _MSC_VER
# ifndef inline
#  define inline __inline
# endif
# ifndef restrict
#  define restrict __restrict
# endif
# ifndef __func__
#  define __func__ __FUNCTION__
# endif
# ifndef STDOUT_FILENO
#  define STDOUT_FILENO _fileno(stdout)
# endif
# ifndef STDERR_FILENO
#  define STDERR_FILENO _fileno(stderr)
# endif
# ifndef S_ISDIR
#  define S_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
# endif
# ifndef S_ISREG
#  define S_ISREG(mode) (((mode) & S_IFMT) == S_IFREG)
# endif
# ifndef S_IXUSR
#   define S_IXUSR S_IEXEC
# endif
#endif // _MSC_VER

#define FNAME_ILLEGAL "\"*?><|" /* illegal characters in a file name */

#define TEMP_DIR_NAMES {"$TMP", "$TEMP", "$USERPROFILE", ""}
#define TEMP_FILE_PATH_MAXLEN _MAX_PATH

#define BASENAMELEN    _MAX_PATH
#define TEMPNAMELEN    _MAX_PATH

#ifdef _MSC_VER
typedef SSIZE_T ssize_t;
#endif

#ifndef SSIZE_MAX
# ifdef _WIN64
#  define SSIZE_MAX _I64_MAX
# else
#  define SSIZE_MAX LONG_MAX
# endif
#endif

typedef uv_uid_t uid_t;

// lines end in CR-NL instead of NL
#define USE_CRNL

#endif  // NVIM_OS_WIN_DEFS_H

#ifndef NVIM_EVENT_PTY_PROCESS_H
#define NVIM_EVENT_PTY_PROCESS_H

#ifdef _WIN32
# include "nvim/os/pty_process_win.h"
#else
# include "nvim/os/pty_process_unix.h"
#endif
#endif  // NVIM_EVENT_PTY_PROCESS_H

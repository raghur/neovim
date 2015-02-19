#ifndef NVIM_TUI_INPUT_H
#define NVIM_TUI_INPUT_H

#include <stdbool.h>

#ifdef UNIX
# include <termkey.h>
#endif
#include "nvim/event/stream.h"
#include "nvim/event/time.h"

typedef struct term_input {
#ifdef UNIX
  int in_fd;
#else
  uv_tty_t in_tty;
#endif
  bool paste_enabled;
  bool waiting;
#ifdef UNIX
  TermKey *tk;
#endif
  TimeWatcher timer_handle;
  Loop *loop;
  Stream read_stream;
  RBuffer *key_buffer;
  uv_mutex_t key_buffer_mutex;
  uv_cond_t key_buffer_cond;
} TermInput;

#ifdef INCLUDE_GENERATED_DECLARATIONS
# include "tui/input.h.generated.h"
#endif

#endif  // NVIM_TUI_INPUT_H

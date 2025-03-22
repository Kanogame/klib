#ifndef KLIB_EXEPT
#define KLIB_EXEPT
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

#define EXIT_WITH_ERROR(str)                                                   \
  {                                                                            \
    printStacktrace(0);                                                        \
    fprintf(stderr, "%s (in %s at %s:%i)\n", str, __func__, __FILE__,          \
            __LINE__);                                                         \
    exit(EXIT_FAILURE);                                                        \
  }

#define EXIT_WITH_ERRNO(str)                                            \
  {                                                                            \
    printStacktrace(0);                                                        \
    printf("%s\n", strerror(errno));                                           \
    fprintf(stderr, "%s %d (in %s at %s:%i)\n", str, errno, __func__,          \
            __FILE__, __LINE__);                                               \
    exit(EXIT_FAILURE);                                                        \
  }

#define MAX_BACKTRACE_LINES 64

static char *_programName;

void printStacktrace(int calledFromSigInt);

int addr2line(char const *const program_name, void const *const addr,
              int lineNb);

void initExceptions(char *programName);
#endif